#include <tiny_log.h>
#include <tiny_socket.h>
#include <TcpClient.h>
#include <device/Property.h>
#include <device/Action.h>
#include <value/JsonString.h>
#include <value/JsonNumber.h>
#include <value/JsonBoolean.h>
#include <DeviceFactory.h>
#include <device/Service.h>
#include <tiny_snprintf.h>
#include "Runner.h"
#include "Modbus.h"
#include "HexString.h"
#include "FanController.h"
#include "DeviceCreator.h"

#define TAG             "sample"

void tiny_print_mem(const char *tag, const char *function)
{

}

void tiny_sleep(int ms)
{

}

void printJsonString(JsonString *value)
{
    printf("value: %s\n", value->value);
}

void printJsonNumber(JsonNumber *value)
{
    if (value->type == JSON_NUMBER_INTEGER)
    {
        printf("value: %ld\n", value->value.intValue);
    }
    else
    {
        printf("value: %f\n", value->value.floatValue);
    }
}

void printJsonBoolean(JsonBoolean *value)
{
    printf("value: %s\n", value->value ? "true" : "false");
}

void printValue(JsonValue *value)
{
    switch (value->type)
    {
        case JSON_STRING:
            printJsonString(value->data.string);
            break;

        case JSON_NUMBER:
            printJsonNumber(value->data.number);
            break;

        case JSON_BOOLEAN:
            printJsonBoolean(value->data.boolean);
            break;

        default:
            printf("value invalid: %d\n", value->type);
            break;
    }
}

#define IID_DEVICE_INFORMATION                          1
#define IID_DEVICE_INFORMATION_MANUFACTURER             1
#define IID_DEVICE_INFORMATION_MODEL                    2
#define IID_DEVICE_INFORMATION_SERIAL_NUMBER            3
#define IID_DEVICE_INFORMATION_FIRMWARE_REVISION        4

#define IID_FAN                                         2
#define IID_FAN_ON                                      1
#define IID_FAN_FAN_LEVEL                               2

#define IID_MODBUS_TRANSMIT                             3
#define IID_MODBUS_TRANSMIT_SEND                        1

#define IID_MODBUS                                      4
#define IID_MODBUS_READ_DISCRETE_INPUTS                 1
#define IID_MODBUS_READ_COILS                           2
#define IID_MODBUS_WRITE_SINGLE_COIL                    3
#define IID_MODBUS_WRITE_MULTIPLE_COILS                 4
#define IID_MODBUS_READ_INPUT_REGISTERS                 5
#define IID_MODBUS_READ_MULTIPLE_HOLDING_REGISTERS      6
#define IID_MODBUS_WRITE_SINGLE_HOLDING_REGISTER        7
#define IID_MODBUS_WRITE_MULTIPLE_HOLDING_REGISTERS     8


static void OnDeviceInformationGet(PropertyOperation *o)
{
    printf("OnDeviceInformationGet: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        case IID_DEVICE_INFORMATION_MANUFACTURER:
            o->value = JsonValue_NewString("GeekCity");
            break;

        case IID_DEVICE_INFORMATION_MODEL:
            o->value = JsonValue_NewString("GeekFan2018");
            break;

        case IID_DEVICE_INFORMATION_SERIAL_NUMBER:
            o->value = JsonValue_NewString("1234567");
            break;

        case IID_DEVICE_INFORMATION_FIRMWARE_REVISION:
            o->value = JsonValue_NewString("1.0.0");
            break;

        default:
            break;
    }
}

static void OnFanGet(PropertyOperation *o)
{
    printf("OnFanGet: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        case IID_FAN_ON:
            o->value = JsonValue_NewBoolean(fan_get_on());
            break;

        case IID_FAN_FAN_LEVEL:
            o->value = JsonValue_NewInteger(2); // bug !!!
            break;

        default:
            break;
    }
}

static void OnPropertyGet(PropertyOperation *o)
{
    printf("OnPropertyGet: did = %s, siid = %d, piid = %d\n", o->pid.did, o->pid.siid, o->pid.iid);

    switch (o->pid.siid)
    {
        case IID_DEVICE_INFORMATION:
            OnDeviceInformationGet(o);
            break;

        case IID_FAN:
            OnFanGet(o);
            break;

        default:
            break;
    }
}

static void OnFanSet(PropertyOperation *o)
{
    printf("OnFanSet: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        case IID_FAN_ON:
            o->status = 0;
            fan_set_on(o->value->data.boolean->value);
            break;

        case IID_FAN_FAN_LEVEL:
            o->status = 0;
            break;

        default:
            break;
    }
}

static void OnPropertySet(PropertyOperation *o)
{
    printf("OnPropertySet: did=[%s], siid = [%d], piid = [%d]\n", o->pid.did, o->pid.siid, o->pid.iid);
    printValue(o->value);

    switch (o->pid.siid)
    {
        case IID_FAN:
            OnFanSet(o);
            break;

        default:
            o->status = -100;
            break;
    }
}

static void OnModbusTransmitActionSend(ActionOperation *o)
{
    do
    {
        JsonValue *data = (JsonValue *)TinyList_GetAt(&o->in.values, 0);
        if (data == NULL)
        {
            o->status = -1;
            break;
        }

        if (data->type != JSON_STRING)
        {
            o->status = -2;
            break;
        }

        JsonValue * result = mb_send(data->data.string);
        if (result == NULL)
        {
            o->status = -3;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&o->out.values, result)))
        {
            JsonValue_Delete(result);
            o->status = -4;
            break;
        }

        o->status = 0;
    } while (false);
}

static void OnModbusTransmitAction(ActionOperation *o)
{
    printf("OnModbusTransmitAction: aiid = [%d]\n", o->aid.iid);

    switch (o->aid.iid)
    {
        case IID_MODBUS_TRANSMIT_SEND:
            OnModbusTransmitActionSend(o);
            break;

        default:
            o->status = -1;
            break;
    }
}

static void OnModbusReadDiscreteInputs(ActionOperation *o)
{
    do
    {
        JsonValue *arg0 = (JsonValue *)TinyList_GetAt(&o->in.values, 0);
        JsonValue *arg1 = (JsonValue *)TinyList_GetAt(&o->in.values, 1);
        JsonValue *arg2 = (JsonValue *)TinyList_GetAt(&o->in.values, 2);

        uint8_t unit = 0;
        uint16_t firstAddress = 0;
        uint16_t numberOfDiscreteInputs = 0;
        JsonValue *discreteInputValues = NULL;
        JsonValue *numberOfBytes = NULL;

        if (arg0 == NULL || arg1 == NULL || arg2 == NULL)
        {
            o->status = -1;
            break;
        }

        if (arg0->type != JSON_STRING || arg1->type != JSON_STRING || arg2->type != JSON_NUMBER)
        {
            o->status = -2;
            break;
        }

        if (decodeHex(arg0->data.string, &unit, 1) != 1)
        {
            o->status = -2;
            break;
        }

        if (decodeHex(arg1->data.string, (uint8_t *)&firstAddress, 2) != 2)
        {
            o->status = -2;
            break;
        }
        firstAddress = ntohs(firstAddress);

        if (arg2->data.number->type != JSON_NUMBER_INTEGER)
        {
            o->status = -2;
            break;
        }

        numberOfDiscreteInputs = (uint16_t) arg2->data.number->value.intValue;
        if (numberOfDiscreteInputs == 0)
        {
            o->status = -2;
            break;
        }

        discreteInputValues = mb_read_discrete_inputs(unit, firstAddress, numberOfDiscreteInputs);
        if (discreteInputValues == NULL)
        {
            o->status = -3;
            break;
        }

        numberOfBytes = JsonValue_NewInteger(discreteInputValues->data.string->length / 2);
        if (numberOfBytes == 0)
        {
            JsonValue_Delete(discreteInputValues);
            o->status = -3;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&o->out.values, numberOfBytes)))
        {
            JsonValue_Delete(numberOfBytes);
            JsonValue_Delete(discreteInputValues);
            o->status = -4;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&o->out.values, discreteInputValues)))
        {
            JsonValue_Delete(discreteInputValues);
            o->status = -4;
            break;
        }

        o->status = 0;
    } while (false);
}

static void OnModbusReadCoils(ActionOperation *o)
{
    do
    {
        JsonValue *arg0 = (JsonValue *)TinyList_GetAt(&o->in.values, 0);
        JsonValue *arg1 = (JsonValue *)TinyList_GetAt(&o->in.values, 1);
        JsonValue *arg2 = (JsonValue *)TinyList_GetAt(&o->in.values, 2);

        uint8_t unit = 0;
        uint16_t firstAddress = 0;
        uint16_t numberOfCoils = 0;
        JsonValue *coilValues = NULL;
        JsonValue *numberOfBytes = NULL;

        if (arg0 == NULL || arg1 == NULL || arg2 == NULL)
        {
            o->status = -1;
            break;
        }

        if (arg0->type != JSON_STRING || arg1->type != JSON_STRING || arg2->type != JSON_NUMBER)
        {
            o->status = -2;
            break;
        }

        if (arg2->data.number->type != JSON_NUMBER_INTEGER)
        {
            o->status = -2;
            break;
        }

        if (decodeHex(arg0->data.string, &unit, 1) != 1)
        {
            o->status = -2;
            break;
        }

        if (decodeHex(arg1->data.string, (uint8_t *)&firstAddress, 2) != 2)
        {
            o->status = -2;
            break;
        }
        firstAddress = ntohs(firstAddress);

        numberOfCoils = (uint16_t) arg2->data.number->value.intValue;
        if (numberOfCoils == 0)
        {
            o->status = -2;
            break;
        }

        coilValues = mb_read_coils(unit, firstAddress, numberOfCoils);
        if (coilValues == NULL)
        {
            o->status = -3;
            break;
        }

        numberOfBytes = JsonValue_NewInteger(coilValues->data.string->length / 2);
        if (numberOfBytes == 0)
        {
            JsonValue_Delete(coilValues);
            o->status = -3;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&o->out.values, numberOfBytes)))
        {
            JsonValue_Delete(numberOfBytes);
            JsonValue_Delete(coilValues);
            o->status = -4;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&o->out.values, coilValues)))
        {
            JsonValue_Delete(coilValues);
            o->status = -4;
            break;
        }

        o->status = 0;
    } while (false);
}

static void OnModbusWriteSingleCoil(ActionOperation *o)
{
    do
    {
        JsonValue *arg0 = (JsonValue *)TinyList_GetAt(&o->in.values, 0);
        JsonValue *arg1 = (JsonValue *)TinyList_GetAt(&o->in.values, 1);
        JsonValue *arg2 = (JsonValue *)TinyList_GetAt(&o->in.values, 2);

        uint8_t unit = 0;
        uint16_t firstAddress = 0;
        uint16_t coilValue = 0;
        int ret = 0;

        if (arg0 == NULL || arg1 == NULL || arg2 == NULL)
        {
            o->status = -1;
            break;
        }

        if (arg0->type != JSON_STRING || arg1->type != JSON_STRING || arg2->type != JSON_STRING)
        {
            o->status = -2;
            break;
        }

        if (decodeHex(arg0->data.string, &unit, 1) != 1)
        {
            o->status = -2;
            break;
        }

        if (decodeHex(arg1->data.string, (uint8_t *)&firstAddress, 2) != 2)
        {
            o->status = -2;
            break;
        }
        firstAddress = ntohs(firstAddress);

        if (decodeHex(arg2->data.string, (uint8_t *)&coilValue, 2) != 2)
        {
            o->status = -2;
            break;
        }
        coilValue = ntohs(coilValue);

        ret = mb_write_single_coil(unit, firstAddress, coilValue);
        if (ret != 0)
        {
            o->status = -3;
            break;
        }

        o->status = 0;
    } while (false);
}

static void OnModbusWriteMultipleCoils(ActionOperation *o)
{
    do
    {
        JsonValue *arg0 = (JsonValue *)TinyList_GetAt(&o->in.values, 0);
        JsonValue *arg1 = (JsonValue *)TinyList_GetAt(&o->in.values, 1);
        JsonValue *arg2 = (JsonValue *)TinyList_GetAt(&o->in.values, 2);
        JsonValue *arg3 = (JsonValue *)TinyList_GetAt(&o->in.values, 3);
        JsonValue *arg4 = (JsonValue *)TinyList_GetAt(&o->in.values, 4);

        uint8_t unit = 0;
        uint16_t firstAddress = 0;
        uint16_t numberOfCoils = 0;
        uint8_t numberOfBytes = 0;
        uint8_t coilValues[256];
        int ret = 0;

        if (arg0 == NULL || arg1 == NULL || arg2 == NULL || arg3 == NULL || arg4 == NULL)
        {
            o->status = -1;
            break;
        }

        if (arg0->type != JSON_STRING
            || arg1->type != JSON_STRING
            || arg2->type != JSON_NUMBER
            || arg3->type != JSON_NUMBER
            || arg4->type != JSON_STRING)
        {
            o->status = -2;
            break;
        }

        if (arg2->data.number->type != JSON_NUMBER_INTEGER || arg3->data.number->type != JSON_NUMBER_INTEGER)
        {
            o->status = -2;
            break;
        }

        if (decodeHex(arg0->data.string, &unit, 1) != 1)
        {
            o->status = -2;
            break;
        }

        if (decodeHex(arg1->data.string, (uint8_t *)&firstAddress, 2) != 2)
        {
            o->status = -2;
            break;
        }
        firstAddress = ntohs(firstAddress);

        numberOfCoils = (uint16_t) arg2->data.number->value.intValue;
        numberOfBytes = (uint8_t) arg3->data.number->value.intValue;

        if (decodeHex(arg4->data.string, coilValues, 256) != numberOfBytes)
        {
            o->status = -2;
            break;
        }

        ret = mb_write_multiple_coils(unit, firstAddress, numberOfCoils, numberOfBytes, coilValues);
        if (ret != 0)
        {
            o->status = -3;
            break;
        }

        o->status = 0;
    } while (false);
}

static void OnModbusReadInputRegisters(ActionOperation *o)
{
    do
    {
        JsonValue *arg0 = (JsonValue *)TinyList_GetAt(&o->in.values, 0);
        JsonValue *arg1 = (JsonValue *)TinyList_GetAt(&o->in.values, 1);
        JsonValue *arg2 = (JsonValue *)TinyList_GetAt(&o->in.values, 2);

        uint8_t unit = 0;
        uint16_t firstAddress = 0;
        uint16_t numberOfRegisters = 0;
        JsonValue *registerValues = NULL;
        JsonValue *numberOfBytes = NULL;

        if (arg0 == NULL || arg1 == NULL || arg2 == NULL)
        {
            o->status = -1;
            break;
        }

        if (arg0->type != JSON_STRING || arg1->type != JSON_STRING || arg2->type != JSON_NUMBER)
        {
            o->status = -2;
            break;
        }

        if (arg2->data.number->type != JSON_NUMBER_INTEGER)
        {
            o->status = -2;
            break;
        }

        if (decodeHex(arg0->data.string, &unit, 1) != 1)
        {
            o->status = -2;
            break;
        }

        if (decodeHex(arg1->data.string, (uint8_t *)&firstAddress, 2) != 2)
        {
            o->status = -2;
            break;
        }
        firstAddress = ntohs(firstAddress);

        numberOfRegisters = (uint16_t) arg2->data.number->value.intValue;
        if (numberOfRegisters == 0)
        {
            o->status = -2;
            break;
        }

        registerValues = mb_read_input_registers(unit, firstAddress, numberOfRegisters);
        if (registerValues == NULL)
        {
            o->status = -3;
            break;
        }

        numberOfBytes = JsonValue_NewInteger(registerValues->data.string->length / 2);
        if (numberOfBytes == 0)
        {
            JsonValue_Delete(registerValues);
            o->status = -3;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&o->out.values, numberOfBytes)))
        {
            JsonValue_Delete(numberOfBytes);
            JsonValue_Delete(registerValues);
            o->status = -4;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&o->out.values, registerValues)))
        {
            JsonValue_Delete(registerValues);
            o->status = -4;
            break;
        }

        o->status = 0;
    } while (false);
}

static void OnModbusReadMultipleHoldingRegisters(ActionOperation *o)
{
    do
    {
        JsonValue *arg0 = (JsonValue *)TinyList_GetAt(&o->in.values, 0);
        JsonValue *arg1 = (JsonValue *)TinyList_GetAt(&o->in.values, 1);
        JsonValue *arg2 = (JsonValue *)TinyList_GetAt(&o->in.values, 2);

        uint8_t unit = 0;
        uint16_t firstAddress = 0;
        uint16_t numberOfRegisters = 0;
        JsonValue *registerValues = NULL;
        JsonValue *numberOfBytes = NULL;

        if (arg0 == NULL || arg1 == NULL || arg2 == NULL)
        {
            o->status = -1;
            break;
        }

        if (arg0->type != JSON_STRING || arg1->type != JSON_STRING || arg2->type != JSON_NUMBER)
        {
            o->status = -2;
            break;
        }

        if (arg2->data.number->type != JSON_NUMBER_INTEGER)
        {
            o->status = -2;
            break;
        }

        if (decodeHex(arg0->data.string, &unit, 1) != 1)
        {
            o->status = -2;
            break;
        }

        if (decodeHex(arg1->data.string, (uint8_t *)&firstAddress, 2) != 2)
        {
            o->status = -2;
            break;
        }
        firstAddress = ntohs(firstAddress);

        numberOfRegisters = (uint16_t) arg2->data.number->value.intValue;
        if (numberOfRegisters == 0)
        {
            o->status = -2;
            break;
        }

        registerValues = mb_read_multiple_holding_registers(unit, firstAddress, numberOfRegisters);
        if (registerValues == NULL)
        {
            o->status = -3;
            break;
        }

        numberOfBytes = JsonValue_NewInteger(registerValues->data.string->length / 2);
        if (numberOfBytes == 0)
        {
            JsonValue_Delete(registerValues);
            o->status = -3;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&o->out.values, numberOfBytes)))
        {
            JsonValue_Delete(numberOfBytes);
            JsonValue_Delete(registerValues);
            o->status = -4;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&o->out.values, registerValues)))
        {
            JsonValue_Delete(registerValues);
            o->status = -4;
            break;
        }

        o->status = 0;
    } while (false);
}

static void OnModbusWriteSingleHoldingRegister(ActionOperation *o)
{
    do
    {
        JsonValue *arg0 = (JsonValue *)TinyList_GetAt(&o->in.values, 0);
        JsonValue *arg1 = (JsonValue *)TinyList_GetAt(&o->in.values, 1);
        JsonValue *arg2 = (JsonValue *)TinyList_GetAt(&o->in.values, 2);

        uint8_t unit = 0;
        uint16_t firstAddress = 0;
        uint16_t registerValue = 0;
        int ret = 0;

        if (arg0 == NULL || arg1 == NULL || arg2 == NULL)
        {
            o->status = -1;
            break;
        }

        if (arg0->type != JSON_STRING || arg1->type != JSON_STRING || arg2->type != JSON_STRING)
        {
            o->status = -2;
            break;
        }

        if (decodeHex(arg0->data.string, &unit, 1) != 1)
        {
            o->status = -2;
            break;
        }

        if (decodeHex(arg1->data.string, (uint8_t *)&firstAddress, 2) != 2)
        {
            o->status = -2;
            break;
        }
        firstAddress = ntohs(firstAddress);

        if (decodeHex(arg2->data.string, (uint8_t *) &registerValue, 2) != 2)
        {
            o->status = -2;
            break;
        }
        registerValue = ntohs(registerValue);

        ret = mb_write_single_holding_register(unit, firstAddress, registerValue);
        if (ret != 0)
        {
            o->status = -3;
            break;
        }

        o->status = 0;
    } while (false);
}

static void OnModbusWriteMultipleHoldingRegisters(ActionOperation *o)
{
    do
    {
        JsonValue *arg0 = (JsonValue *)TinyList_GetAt(&o->in.values, 0);
        JsonValue *arg1 = (JsonValue *)TinyList_GetAt(&o->in.values, 1);
        JsonValue *arg2 = (JsonValue *)TinyList_GetAt(&o->in.values, 2);
        JsonValue *arg3 = (JsonValue *)TinyList_GetAt(&o->in.values, 3);
        JsonValue *arg4 = (JsonValue *)TinyList_GetAt(&o->in.values, 4);

        uint8_t unit = 0;
        uint16_t firstAddress = 0;
        uint16_t numberOfRegisters = 0;
        uint8_t numberOfBytes = 0;
        uint8_t registerValues[256];
        int ret = 0;

        if (arg0 == NULL || arg1 == NULL || arg2 == NULL || arg3 == NULL || arg4 == NULL)
        {
            o->status = -1;
            break;
        }

        if (arg0->type != JSON_STRING
            || arg1->type != JSON_STRING
            || arg2->type != JSON_NUMBER
            || arg3->type != JSON_NUMBER
            || arg4->type != JSON_STRING)
        {
            o->status = -2;
            break;
        }

        if (arg2->data.number->type != JSON_NUMBER_INTEGER || arg3->data.number->type != JSON_NUMBER_INTEGER)
        {
            o->status = -2;
            break;
        }

        if (decodeHex(arg0->data.string, &unit, 1) != 1)
        {
            o->status = -2;
            break;
        }

        if (decodeHex(arg1->data.string, (uint8_t *)&firstAddress, 2) != 2)
        {
            o->status = -2;
            break;
        }
        firstAddress = ntohs(firstAddress);

        numberOfRegisters = (uint16_t) arg2->data.number->value.intValue;
        numberOfBytes = (uint8_t) arg3->data.number->value.intValue;

        if (numberOfRegisters == 0 || numberOfBytes == 0)
        {
            o->status = -2;
            break;
        }

        if (decodeHex(arg4->data.string, registerValues, 256) != numberOfBytes)
        {
            o->status = -2;
            break;
        }

        ret = mb_write_multiple_holding_registers(unit, firstAddress, numberOfRegisters, numberOfBytes, registerValues);
        if (ret != 0)
        {
            o->status = -3;
            break;
        }

        o->status = 0;
    } while (false);
}

static void OnModbusAction(ActionOperation *o)
{
    printf("OnSwitchAction: aiid = [%d]\n", o->aid.iid);

    switch (o->aid.iid)
    {
        case IID_MODBUS_READ_DISCRETE_INPUTS:
            OnModbusReadDiscreteInputs(o);
            break;

        case IID_MODBUS_READ_COILS:
            OnModbusReadCoils(o);
            break;

        case IID_MODBUS_WRITE_SINGLE_COIL:
            OnModbusWriteSingleCoil(o);
            break;

        case IID_MODBUS_WRITE_MULTIPLE_COILS:
            OnModbusWriteMultipleCoils(o);
            break;

        case IID_MODBUS_READ_INPUT_REGISTERS:
            OnModbusReadInputRegisters(o);
            break;

        case IID_MODBUS_READ_MULTIPLE_HOLDING_REGISTERS:
            OnModbusReadMultipleHoldingRegisters(o);
            break;

        case IID_MODBUS_WRITE_SINGLE_HOLDING_REGISTER:
            OnModbusWriteSingleHoldingRegister(o);
            break;

        case IID_MODBUS_WRITE_MULTIPLE_HOLDING_REGISTERS:
            OnModbusWriteMultipleHoldingRegisters(o);
            break;

        default:
            o->status = -1;
            break;
    }
}

static void OnActionInvoke(ActionOperation *o)
{
    printf("OnActionInvoke: did=[%s], siid = [%d], aiid = [%d]\n", o->aid.did, o->aid.siid, o->aid.iid);

    switch (o->aid.siid)
    {
        case IID_MODBUS_TRANSMIT:
            OnModbusTransmitAction(o);
            break;

        case IID_MODBUS:
            OnModbusAction(o);
            break;

        default:
            break;
    }
}

#define DID                 "10001"
#define PRODUCT_ID          10006
#define PRODUCT_VERSION     1
#define LTSK                "+NC/fa+QFz6hHtcOUKUJK9EQEl/J1nKhh2ixj9hQtGU="

//static void Switch_On_Changed(bool value)
//{
//    TinyRet ret = TINY_RET_OK;
//    PropertyOperation *o = PropertyOperation_New();
//
//    strncpy(o->pid.did, DID, DEVICE_ID_LENGTH);
//    o->status = 0;
//    o->pid.siid = 2;
//    o->pid.iid = 1;
//    o->value = JsonValue_NewBoolean(value);
//    if (o->value == NULL)
//    {
//        printf("JsonValue_NewBoolean failed");
//        PropertyOperation_Delete(o);
//        return;
//    }
//
//    ret = Runner_ChangePropertyValue(o);
//    if (RET_FAILED(ret))
//    {
//        printf("Device_TryChangePropertyValue error: %d", ret);
//    }
//
//    PropertyOperation_Delete(o);
//}

static TinyRet run(const char *ip)
{
    TinyRet ret = TINY_RET_OK;

    /**
     * 1. 初始化设备
     * 参数:
     *      DID: 设备ID
     *      TYPE: 设备类型
     *      LTSK: 设备私钥
     *      10: 超时时间
     */
    Device *device = Device_CreateFrom(DID, PRODUCT_ID, PRODUCT_VERSION, LTSK, "./dd.json");
//    Device *device = DeviceFactory_Create(DID, PRODUCT_ID, PRODUCT_VERSION, LTSK, 10);
    if (device == NULL)
    {
        LOG_E(TAG, "DeviceFactory_Create FAILED!");
        return TINY_RET_E_INTERNAL;
    }

    strncpy(device->ip, ip, TINY_IP_LEN);
    device->port = 9898;

    LOG_I(TAG, "DeviceFactory_Create succeed!");
    LOG_I(TAG, "did: %s", device->did);
    LOG_I(TAG, "product-id: %d", device->productId);
    LOG_I(TAG, "product-version: %d", device->productVersion);

    /**
     * 2. 设置回调函数
     * 参数:
     *      OnPropertyGet: 读属性的回调函数
     *      OnPropertySet: 写属性的回调函数
     *      OnActionInvoke: 方法执行的回调函数
     */
    Device_SetHandler(device, OnPropertyGet, OnPropertySet, OnActionInvoke);

    /**
     * 3. 运行,　如果不出错将不会返回．
     */
    ret = Runner_Run(device);
    if (RET_FAILED(ret))
    {
        LOG_E(TAG, "Runner Finished: %d", ret);
    }

    /**
     * 4. 销毁设备
     */
    Device_Delete(device);

    return ret;
}

static void printUsage(const char *name)
{
    printf("usage: \n");
    printf("    %s ip\n", name);
}

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
	 printUsage(argv[0]);
         return 0;
    }

    tiny_socket_initialize();

    run(argv[1]);

    tiny_socket_finalize();
    return 0;
}

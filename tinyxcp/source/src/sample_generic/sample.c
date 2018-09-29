#include <tiny_log.h>
#include <tiny_socket.h>
#include <device/Property.h>
#include <device/Action.h>
#include <value/JsonString.h>
#include <value/JsonNumber.h>
#include <value/JsonBoolean.h>
#include <DeviceFactory.h>
#include <device/Service.h>
#include "MyDevice.h"

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
#define IID_DEVICE_INFORMATION_IDENTIFY                 1
#define IID_DEVICE_INFORMATION_MANUFACTURER             2
#define IID_DEVICE_INFORMATION_MODEL                    3
#define IID_DEVICE_INFORMATION_NAME                     4
#define IID_DEVICE_INFORMATION_SERIAL_NUMBER            5
#define IID_DEVICE_INFORMATION_FIRMWARE_REVISION        6
#define IID_FAN                                         2
#define IID_FAN_ON                                      1

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

        case IID_DEVICE_INFORMATION_NAME:
            o->value = JsonValue_NewString("GeekFan");
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
            o->value = JsonValue_NewBoolean(false);
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

static void OnDeviceInformationSet(PropertyOperation *o)
{
    printf("OnDeviceInformationSet: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        case IID_DEVICE_INFORMATION_IDENTIFY:
            o->status = 0;
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
        case IID_DEVICE_INFORMATION:
            OnDeviceInformationSet(o);
            break;

        case IID_FAN:
            OnFanSet(o);
            break;

        default:
            break;
    }
}

static void OnActionInvoke(ActionOperation *o)
{
    printf("OnActionInvoke: did=[%s], siid = [%d], piid = [%d]\n", o->aid.did, o->aid.siid, o->aid.iid);
    // o->in
}

#define DID                 "10001"
#define PRODUCT_ID          10005
#define PRODUCT_VERSION     1
#define LTSK                "uJqYa21LsJPIRWgL+PM66h9mRoTtPZU0gYBC7WE1QGg="
//#define TYPE                "urn:homekit-spec:device:fan:00000000:geekcity-ds:1"

static void Fan_On_Changed(bool value)
{
    TinyRet ret = TINY_RET_OK;
    PropertyOperation *o = PropertyOperation_New();

    strncpy(o->pid.did, DID, DEVICE_ID_LENGTH);
    o->status = 0;
    o->pid.siid = 2;
    o->pid.iid = 1;
    o->value = JsonValue_NewBoolean(value);
    if (o->value == NULL)
    {
        printf("JsonValue_NewBoolean failed");
        PropertyOperation_Delete(o);
        return;
    }

    ret = MyDevice_ChangePropertyValue(o);
    if (RET_FAILED(ret))
    {
        printf("Device_TryChangePropertyValue error: %d", ret);
    }

    PropertyOperation_Delete(o);
}

//static void reset(void)
//{
//    TinyRet ret = MyDevice_ResetAccessKey();
//    if (RET_FAILED(ret))
//    {
//        printf("MyDevice_Reset error: %d", ret);
//    }
//}
//
//static void get_access_key(void)
//{
//    TinyRet ret = MyDevice_GetAccessKey();
//    if (RET_FAILED(ret))
//    {
//        printf("MyDevice_GetAccessKey error: %d", ret);
//    }
//}

static TinyRet run(void)
{
    TinyRet ret = TINY_RET_OK;

    /**
     * 1. 初始化设备
     * 参数:
     *      DID: 设备ID
     *      PRODUCT_ID: 产品ID
     *      PRODUCT_VERSION: 产品版本
     *      LTSK: 设备私钥
     *      10: 超时时间
     */
    Device *device = DeviceFactory_Create(DID, PRODUCT_ID, PRODUCT_VERSION, LTSK, 10);
    if (device == NULL)
    {
        LOG_E(TAG, "DeviceFactory_Create FAILED!");
        return TINY_RET_E_INTERNAL;
    }

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
    ret = MyDevice_Run(device);
    if (RET_FAILED(ret))
    {
        LOG_E(TAG, "MyDevice Finished: %d", ret);
    }

    /**
     * 4. 销毁设备
     */
    Device_Delete(device);

    return ret;
}

int main(void)
{
    tiny_socket_initialize();

    run();

    tiny_socket_finalize();
    return 0;
}

/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   Modbus.c
*
* @remark
*
*/

#include <TcpClient.h>
#include <value/JsonString.h>
#include <tiny_print_binary.h>
#include "Modbus.h"
#include "HexString.h"
#include "ModFrame.h"

//#define IP      "10.0.1.8"
#define IP      "192.168.0.232"
#define PORT    502

TinyRet sendBytes(TcpExchange *exchange)
{
    TinyRet ret = TINY_RET_OK;
    TcpClient *client = NULL;

    do
    {
        tiny_print_binary("sendBytes", (const uint8_t *)exchange->content, exchange->length, true);

        client = TcpClient_New();
        if (client == NULL)
        {
            printf("TcpClient_New FAILED\n");
            ret = TINY_RET_E_NEW;
            break;
        }

        ret = TcpClient_Send(client, exchange);
        if (RET_FAILED(ret))
        {
            printf("TcpClient_Send FAILED\n");
            break;
        }

        tiny_print_binary("recvBytes", (const uint8_t *)exchange->content, exchange->length, true);
    } while (false);

    if (client != NULL)
    {
        TcpClient_Delete(client);
    }

    return ret;
}

JsonValue * mb_send(JsonString *request)
{
    JsonValue *response = NULL;
    TcpClient *client = NULL;
    TcpExchange *exchange = NULL;

    printf("data: %s\n", request->value);

    do
    {
        uint8_t bytes[1024];
        uint32_t length = 0;

        memset(bytes, 0, 1024);
        length = decodeHex(request, bytes, 1024);

        client = TcpClient_New();
        if (client == NULL)
        {
            printf("TcpClient_New FAILED\n");
            break;
        }

        exchange = TcpExchange_New(IP, PORT, 1, bytes, length);
        if (exchange == NULL)
        {
            printf("TcpExchange_New FAILED\n");
            break;
        }

        if (RET_FAILED(TcpClient_Send(client, exchange)))
        {
            printf("TcpClient_Send FAILED\n");
            break;
        }

        response = encodeHex((uint8_t *)exchange->content, exchange->length);
        if (response == NULL)
        {
            printf("encodeHex FAILED\n");
            break;
        }
    } while (false);

    if (client != NULL)
    {
        TcpClient_Delete(client);
    }

    if (exchange != NULL)
    {
        TcpExchange_Delete(exchange);
    }

    return response;
}

JsonValue * mb_read_discrete_inputs(uint8_t unit, uint16_t firstAddress, uint16_t numberOfDiscreteInputs)
{
    JsonValue *value = NULL;
    TcpExchange *exchange = NULL;

    do
    {
        uint16_t payloadLength = 6;
        ModFrame query;
        ModFrame *result = NULL;
        uint8_t numberOfBytes = 0;

        query.transactionIdentifier = 0;
        query.protocolIdentifier = MODBUS_TCP;
        query.length = htons(payloadLength);
        query.unitIdentifier = unit;
        query.functionCode = READ_DISCRETE_INPUTS;
        query.data[0] = (uint8_t)(firstAddress >> 8);
        query.data[1] = (uint8_t)(firstAddress);
        query.data[2] = (uint8_t)(numberOfDiscreteInputs >> 8);
        query.data[3] = (uint8_t)(numberOfDiscreteInputs);

        exchange = TcpExchange_New(IP, PORT, 1, (uint8_t *) &query, 6 + payloadLength);
        if (exchange == NULL)
        {
            printf("TcpExchange_New failed\n");
            break;
        }

        if (RET_FAILED(sendBytes(exchange)))
        {
            printf("sendBytes failed\n");
            break;
        }

        result = (ModFrame *)exchange->content;
        if (result->transactionIdentifier != query.transactionIdentifier)
        {
            printf("invalid transactionIdentifier: %04x\n", result->transactionIdentifier);
            break;
        }

        if (result->protocolIdentifier != MODBUS_TCP)
        {
            printf("invalid protocolIdentifier: %04x\n", result->protocolIdentifier);
            break;
        }

        if (result->length == 0)
        {
            printf("invalid length: 0\n");
            break;
        }

        if (result->unitIdentifier != query.unitIdentifier)
        {
            printf("invalid unitIdentifier: %02x\n", result->unitIdentifier);
            break;
        }

        if (result->functionCode != query.functionCode)
        {
            printf("invalid functionCode: %02x\n", result->functionCode);
            break;
        }

        printf("result->length: %d\n", ntohs(result->length));

        numberOfBytes = result->data[0];
        value = encodeHex(result->data + 1, numberOfBytes);
    } while (false);

    if (exchange != NULL)
    {
        TcpExchange_Delete(exchange);
    }

    return value;
}

JsonValue * mb_read_coils(uint8_t unit, uint16_t firstAddress, uint16_t numberOfCoils)
{
    JsonValue *value = NULL;
    TcpExchange *exchange = NULL;

    do
    {
        uint16_t payloadLength = 6;
        ModFrame query;
        ModFrame *result = NULL;
        uint8_t numberOfBytes;

        query.transactionIdentifier = 0;
        query.protocolIdentifier = MODBUS_TCP;
        query.length = htons(payloadLength);
        query.unitIdentifier = unit;
        query.functionCode = READ_COILS;
        query.data[0] = (uint8_t)(firstAddress >> 8);
        query.data[1] = (uint8_t)(firstAddress);
        query.data[2] = (uint8_t)(numberOfCoils >> 8);
        query.data[3] = (uint8_t)(numberOfCoils);

        exchange = TcpExchange_New(IP, PORT, 1, (uint8_t *) &query, 6 + payloadLength);
        if (exchange == NULL)
        {
            printf("TcpExchange_New failed\n");
            break;
        }

        if (RET_FAILED(sendBytes(exchange)))
        {
            printf("sendBytes failed\n");
            break;
        }

        result = (ModFrame *)exchange->content;
        if (result->transactionIdentifier != query.transactionIdentifier)
        {
            printf("invalid transactionIdentifier: %04x\n", result->transactionIdentifier);
            break;
        }

        if (result->protocolIdentifier != MODBUS_TCP)
        {
            printf("invalid protocolIdentifier: %02x\n", result->protocolIdentifier);
            break;
        }

        if (result->length == 0)
        {
            printf("invalid length: 0\n");
            break;
        }

        if (result->unitIdentifier != query.unitIdentifier)
        {
            printf("invalid unitIdentifier: %02x\n", result->unitIdentifier);
            break;
        }

        if (result->functionCode != query.functionCode)
        {
            printf("invalid functionCode: %02x\n", result->functionCode);
            break;
        }

        printf("result->length: %d\n", ntohs(result->length));

        numberOfBytes = result->data[0];
        value = encodeHex(result->data + 1, numberOfBytes);
    } while (false);

    if (exchange != NULL)
    {
        TcpExchange_Delete(exchange);
    }

    return value;
}

int mb_write_single_coil(uint8_t unit, uint16_t firstAddress, uint16_t coilValue)
{
    int ret = 0;
    TcpExchange *exchange = NULL;

    do
    {
        uint16_t payloadLength = 6;
        uint16_t resultPayloadLength = 0;
        ModFrame query;
        ModFrame *result = NULL;

        query.transactionIdentifier = 0;
        query.protocolIdentifier = MODBUS_TCP;
        query.length = htons(payloadLength);
        query.unitIdentifier = unit;
        query.functionCode = WRITE_SINGLE_COIL;
        query.data[0] = (uint8_t)(firstAddress >> 8);
        query.data[1] = (uint8_t)(firstAddress);
        query.data[2] = (uint8_t)(coilValue >> 8);
        query.data[3] = (uint8_t)(coilValue);

        exchange = TcpExchange_New(IP, PORT, 1, (uint8_t *) &query, 6 + payloadLength);
        if (exchange == NULL)
        {
            ret = -1;
            break;
        }

        if (RET_FAILED(sendBytes(exchange)))
        {
            ret = -2;
            break;
        }

        result = (ModFrame *)exchange->content;
        if (result->transactionIdentifier != query.transactionIdentifier)
        {
            printf("invalid transactionIdentifier: %02x\n", result->transactionIdentifier);
            ret = -3;
            break;
        }

        if (result->protocolIdentifier != MODBUS_TCP)
        {
            printf("invalid protocolIdentifier: %02x\n", result->protocolIdentifier);
            ret = -4;
            break;
        }

        resultPayloadLength = ntohs(result->length);
        printf("result->length: %d\n", resultPayloadLength);

        if (resultPayloadLength != payloadLength)
        {
            printf("invalid payload length: %d\n", resultPayloadLength);
            ret = -5;
            break;
        }

        if (result->unitIdentifier != query.unitIdentifier)
        {
            printf("invalid unitIdentifier: %02x\n", result->unitIdentifier);
            ret = -5;
            break;
        }

        if (result->functionCode != query.functionCode)
        {
            printf("invalid functionCode: %02x\n", result->functionCode);
            ret = -5;
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            if (query.data[i] != result->data[i])
            {
                ret = -5;
                break;
            }
        }
    } while (false);

    if (exchange != NULL)
    {
        TcpExchange_Delete(exchange);
    }

    return ret;
}

int mb_write_multiple_coils(uint8_t unit, uint16_t firstAddress, uint16_t numberOfCoils, uint8_t numberOfBytes, uint8_t *coilValues)
{
    int ret = 0;
    TcpExchange *exchange = NULL;

    do
    {
        uint16_t payloadLength = (uint16_t) (7 + numberOfBytes);
        ModFrame query;
        ModFrame *result = NULL;

        query.transactionIdentifier = 0;
        query.protocolIdentifier = MODBUS_TCP;
        query.length = htons(payloadLength);
        query.unitIdentifier = unit;
        query.functionCode = WRITE_MULTIPLE_COILS;
        query.data[0] = (uint8_t)(firstAddress >> 8);
        query.data[1] = (uint8_t)(firstAddress);
        query.data[2] = (uint8_t)(numberOfCoils >> 8);
        query.data[3] = (uint8_t)(numberOfCoils);
        query.data[4] = numberOfBytes;

        for (uint8_t i = 0; i < numberOfBytes; ++i)
        {
            query.data[5 + i] = coilValues[i];
        }

        exchange = TcpExchange_New(IP, PORT, 1, (uint8_t *) &query, 6 + payloadLength);
        if (exchange == NULL)
        {
            ret = -1;
            break;
        }

        if (RET_FAILED(sendBytes(exchange)))
        {
            ret = -2;
            break;
        }

        result = (ModFrame *)exchange->content;
        if (result->transactionIdentifier != query.transactionIdentifier)
        {
            printf("invalid transactionIdentifier: %02x\n", result->transactionIdentifier);
            ret = -3;
            break;
        }

        if (result->protocolIdentifier != MODBUS_TCP)
        {
            printf("invalid protocolIdentifier: %02x\n", result->protocolIdentifier);
            ret = -4;
            break;
        }

        printf("result->length: %d", result->length);
    } while (false);

    if (exchange != NULL)
    {
        TcpExchange_Delete(exchange);
    }

    return ret;
}

JsonValue * mb_read_input_registers(uint8_t unit, uint16_t firstAddress, uint16_t numberOfRegisters)
{
    JsonValue *value = NULL;
    TcpExchange *exchange = NULL;

    do
    {
        uint16_t payloadLength = 6;
        uint16_t resultPayloadLength = 0;
        ModFrame query;
        ModFrame *result = NULL;
        uint8_t numberOfBytes;

        query.transactionIdentifier = 0;
        query.protocolIdentifier = MODBUS_TCP;
        query.length = htons(payloadLength);
        query.unitIdentifier = unit;
        query.functionCode = READ_INPUT_REGISTERS;
        query.data[0] = (uint8_t)(firstAddress >> 8);
        query.data[1] = (uint8_t)(firstAddress);
        query.data[2] = (uint8_t)(numberOfRegisters >> 8);
        query.data[3] = (uint8_t)(numberOfRegisters);

        exchange = TcpExchange_New(IP, PORT, 1, (uint8_t *) &query, 6 + payloadLength);
        if (exchange == NULL)
        {
            break;
        }

        if (RET_FAILED(sendBytes(exchange)))
        {
            break;
        }

        result = (ModFrame *)exchange->content;
        if (result->transactionIdentifier != query.transactionIdentifier)
        {
            printf("invalid transactionIdentifier: %02x\n", result->transactionIdentifier);
            break;
        }

        if (result->protocolIdentifier != MODBUS_TCP)
        {
            printf("invalid protocolIdentifier: %02x\n", result->protocolIdentifier);
            break;
        }

        resultPayloadLength = ntohs(result->length);
        printf("resultPayloadLength: %d\n", resultPayloadLength);

        if (resultPayloadLength == 0)
        {
            printf("invalid result payload length: %d\n", resultPayloadLength);
            break;
        }

        if (result->unitIdentifier != query.unitIdentifier)
        {
            printf("invalid unitIdentifier: %02x\n", result->unitIdentifier);
            break;
        }

        if (result->functionCode != query.functionCode)
        {
            printf("invalid functionCode: %02x\n", result->functionCode);
            break;
        }

        numberOfBytes = result->data[0];
        value = encodeHex(result->data + 1, numberOfBytes);
    } while (false);

    if (exchange != NULL)
    {
        TcpExchange_Delete(exchange);
    }

    return value;
}

JsonValue * mb_read_multiple_holding_registers(uint8_t unit, uint16_t firstAddress, uint16_t numberOfRegisters)
{
    JsonValue *value = NULL;
    TcpExchange *exchange = NULL;

    do
    {
        uint16_t payloadLength = 6;
        uint16_t resultPayloadLength = 0;
        ModFrame query;
        ModFrame *result = NULL;
        uint8_t numberOfBytes;

        query.transactionIdentifier = 0;
        query.protocolIdentifier = MODBUS_TCP;
        query.length = htons(payloadLength);
        query.unitIdentifier = unit;
        query.functionCode = READ_MULTIPLE_HOLDING_REGISTERS;
        query.data[0] = (uint8_t)(firstAddress >> 8);
        query.data[1] = (uint8_t)(firstAddress);
        query.data[2] = (uint8_t)(numberOfRegisters >> 8);
        query.data[3] = (uint8_t)(numberOfRegisters);

        exchange = TcpExchange_New(IP, PORT, 1, (uint8_t *) &query, 6 + payloadLength);
        if (exchange == NULL)
        {
            break;
        }

        if (RET_FAILED(sendBytes(exchange)))
        {
            break;
        }

        result = (ModFrame *)exchange->content;
        if (result->transactionIdentifier != query.transactionIdentifier)
        {
            printf("invalid transactionIdentifier: %02x\n", result->transactionIdentifier);
            break;
        }

        if (result->protocolIdentifier != MODBUS_TCP)
        {
            printf("invalid protocolIdentifier: %02x\n", result->protocolIdentifier);
            break;
        }

        resultPayloadLength = ntohs(result->length);
        printf("resultPayloadLength: %d\n", resultPayloadLength);

        if (resultPayloadLength == 0)
        {
            printf("invalid result payload length: %d\n", resultPayloadLength);
            break;
        }

        if (result->unitIdentifier != query.unitIdentifier)
        {
            printf("invalid unitIdentifier: %02x\n", result->unitIdentifier);
            break;
        }

        if (result->functionCode != query.functionCode)
        {
            printf("invalid functionCode: %02x\n", result->functionCode);
            break;
        }

        numberOfBytes = result->data[0];
        value = encodeHex(result->data + 1, numberOfBytes);
    } while (false);

    if (exchange != NULL)
    {
        TcpExchange_Delete(exchange);
    }

    return value;
}

int mb_write_single_holding_register(uint8_t unit, uint16_t firstAddress, uint16_t registerValue)
{
    int ret = 0;
    TcpExchange *exchange = NULL;

    do
    {
        uint16_t payloadLength = 6;
        uint16_t resultPayloadLength = 0;
        ModFrame query;
        ModFrame *result = NULL;

        query.transactionIdentifier = 0;
        query.protocolIdentifier = MODBUS_TCP;
        query.length = htons(payloadLength);
        query.unitIdentifier = unit;
        query.functionCode = WRITE_SINGLE_HOLDING_REGISTER;
        query.data[0] = (uint8_t)(firstAddress >> 8);
        query.data[1] = (uint8_t)(firstAddress);
        query.data[2] = (uint8_t)(registerValue >> 8);
        query.data[3] = (uint8_t)(registerValue);

        exchange = TcpExchange_New(IP, PORT, 1, (uint8_t *) &query, 6 + payloadLength);
        if (exchange == NULL)
        {
            ret = -1;
            break;
        }

        if (RET_FAILED(sendBytes(exchange)))
        {
            ret = -2;
            break;
        }

        result = (ModFrame *)exchange->content;
        if (result->transactionIdentifier != query.transactionIdentifier)
        {
            printf("invalid transactionIdentifier: %02x\n", result->transactionIdentifier);
            ret = -3;
            break;
        }

        if (result->protocolIdentifier != MODBUS_TCP)
        {
            printf("invalid protocolIdentifier: %02x\n", result->protocolIdentifier);
            ret = -4;
            break;
        }

        resultPayloadLength = ntohs(result->length);
        printf("result->length: %d\n", resultPayloadLength);

        if (resultPayloadLength != payloadLength)
        {
            printf("invalid payload length: %d\n", resultPayloadLength);
            ret = -5;
            break;
        }

        if (result->unitIdentifier != query.unitIdentifier)
        {
            printf("invalid unitIdentifier: %02x\n", result->unitIdentifier);
            ret = -5;
            break;
        }

        if (result->functionCode != query.functionCode)
        {
            printf("invalid functionCode: %02x\n", result->functionCode);
            ret = -5;
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            if (query.data[i] != result->data[i])
            {
                ret = -5;
                break;
            }
        }
    } while (false);

    if (exchange != NULL)
    {
        TcpExchange_Delete(exchange);
    }

    return ret;
}

int mb_write_multiple_holding_registers(uint8_t unit, uint16_t firstAddress, uint16_t numberOfRegisters, uint8_t numberOfBytes, uint8_t *registerValues)
{
    int ret = 0;
    TcpExchange *exchange = NULL;

    do
    {
        uint16_t payloadLength = (uint16_t) (7 + numberOfBytes);
        ModFrame query;
        ModFrame *result = NULL;

        query.transactionIdentifier = 0;
        query.protocolIdentifier = MODBUS_TCP;
        query.length = htons(payloadLength);
        query.unitIdentifier = unit;
        query.functionCode = WRITE_MULTIPLE_HOLDING_REGISTERS;
        query.data[0] = (uint8_t)(firstAddress >> 8);
        query.data[1] = (uint8_t)(firstAddress);
        query.data[2] = (uint8_t)(numberOfRegisters >> 8);
        query.data[3] = (uint8_t)(numberOfRegisters);
        query.data[4] = numberOfBytes;

        for (uint8_t i = 0; i < numberOfBytes; ++i)
        {
            query.data[5 + i] = registerValues[i];
        }

        exchange = TcpExchange_New(IP, PORT, 1, (uint8_t *) &query, 6 + payloadLength);
        if (exchange == NULL)
        {
            ret = -1;
            break;
        }

        if (RET_FAILED(sendBytes(exchange)))
        {
            ret = -2;
            break;
        }

        result = (ModFrame *)exchange->content;
        if (result->transactionIdentifier != query.transactionIdentifier)
        {
            printf("invalid transactionIdentifier: %02x\n", result->transactionIdentifier);
            ret = -3;
            break;
        }

        if (result->protocolIdentifier != MODBUS_TCP)
        {
            printf("invalid protocolIdentifier: %02x\n", result->protocolIdentifier);
            ret = -4;
            break;
        }

        printf("result->length: %d", result->length);
    } while (false);

    if (exchange != NULL)
    {
        TcpExchange_Delete(exchange);
    }

    return ret;
}

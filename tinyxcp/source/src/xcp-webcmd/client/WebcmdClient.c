/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   WebcmdClient.c
 *
 * @remark
 *
 */

#include <HttpClient.h>
#include <tiny_log.h>
#include <JsonObject.h>
#include <JsonArray.h>
#include "WebcmdClient.h"

#define TAG "WebcmdClient"

bool WebcmdClient_ResetAccessKey(uint16_t port)
{
    bool ret = false;
    HttpClient *client = NULL;
    HttpExchange *exchange = NULL;

    do
    {
        client = HttpClient_New();
        if (client == NULL)
        {
            break;
        }

        exchange = HttpExchange_New("127.0.0.1", port, "PUT", "/accesskey", 3, NULL, 0);
        if (exchange == NULL)
        {
            break;
        }

        if (RET_FAILED(HttpClient_Send(client, exchange)))
        {
            break;
        }

        if (exchange->status != 200)
        {
            LOG_D(TAG, "reset access key failed: %d\n", exchange->status);
            break;
        }

        LOG_D(TAG, "reset access key succeed!\n");
        ret = true;
    } while (false);

    if (client != NULL)
    {
        HttpClient_Delete(client);
    }

    if (exchange != NULL)
    {
        HttpExchange_Delete(exchange);
    }

    return ret;
}

TINY_LOR
bool WebcmdClient_GetAccessKey(uint16_t port, char key[XCP_ACCESS_KEY_LEN])
{
    bool ret = false;

    HttpClient *client = NULL;
    HttpExchange *exchange = NULL;
    JsonObject *object = NULL;

    do
    {
        client = HttpClient_New();
        if (client == NULL)
        {
            break;
        }

        exchange = HttpExchange_New("127.0.0.1", port, "GET", "/accesskey", 3, NULL, 0);
        if (exchange == NULL)
        {
            break;
        }

        if (RET_FAILED(HttpClient_Send(client, exchange)))
        {
            break;
        }

        if (exchange->status != 200)
        {
            LOG_D(TAG, "get access key failed: %d\n", exchange->status);
            break;
        }

        if (exchange->content == NULL)
        {
            LOG_D(TAG, "get access key error, content is empty\n");
            break;
        }

        LOG_D(TAG, "get access key: %s\n", exchange->content);

        object = JsonObject_NewString(exchange->content);
        if (object == NULL)
        {
            break;
        }

        JsonString *string = JsonObject_GetString(object, "key");
        if (string == NULL)
        {
            break;
        }

        strncpy(key, string->value, XCP_ACCESS_KEY_LEN);
        ret = true;
    } while (false);

    if (client != NULL)
    {
        HttpClient_Delete(client);
    }

    if (exchange != NULL)
    {
        HttpExchange_Delete(exchange);
    }

    if (object != NULL)
    {
        JsonObject_Delete(object);
    }

    return ret;
}

bool WebcmdClient_SendPropertyChanged(uint16_t port, const char *did, uint16_t siid, uint16_t piid, JsonValue *newValue)
{
    bool ret = false;
    HttpClient *client = NULL;
    HttpExchange *exchange = NULL;
    JsonObject *object = NULL;

    do
    {
        if (newValue == NULL)
        {
            LOG_D(TAG, "newValue is null!\n");
            break;
        }

        object = JsonObject_New();
        if (object == NULL)
        {
            LOG_D(TAG, "JsonObject_New failed!\n");
            break;
        }

        JsonObject_PutString(object, "did", did);
        JsonObject_PutInteger(object, "siid", siid);
        JsonObject_PutInteger(object, "piid", piid);
        JsonObject_PutValue(object, "value", JsonValue_NewFrom(newValue));

        if (RET_FAILED(JsonObject_Encode(object, false)))
        {
            LOG_D(TAG, "JsonObject_Encode failed!\n");
            break;
        }

        client = HttpClient_New();
        if (client == NULL)
        {
            LOG_D(TAG, "HttpClient_New failed!\n");
            break;
        }

        exchange = HttpExchange_New("127.0.0.1", port, "PUT", "/property", 3, NULL, 0);
        if (exchange == NULL)
        {
            LOG_D(TAG, "HttpExchange_New failed!\n");
            break;
        }

        if (RET_FAILED(HttpClient_Send(client, exchange)))
        {
            LOG_D(TAG, "HttpClient_Send failed!\n");
            break;
        }

        if (exchange->status != 200)
        {
            LOG_D(TAG, "property changed failed: %d\n", exchange->status);
            break;
        }

        LOG_D(TAG, "property changed succeed!\n");

        ret = true;
    } while (false);

    if (client != NULL)
    {
        HttpClient_Delete(client);
    }

    if (exchange != NULL)
    {
        HttpExchange_Delete(exchange);
    }

    if (object != NULL)
    {
        JsonObject_Delete(object);
    }

    return ret;
}

bool WebcmdClient_SendEventOccurred(uint16_t port, const char *did, uint16_t siid, uint16_t eiid, JsonArray *arguments)
{
    bool ret = false;
    HttpClient *client = NULL;
    HttpExchange *exchange = NULL;
    JsonObject *object = NULL;

    do
    {
        object = JsonObject_New();
        if (object == NULL)
        {
            printf("JsonObject_New failed!\n");
            break;
        }

        JsonObject_PutString(object, "did", did);
        JsonObject_PutInteger(object, "siid", siid);
        JsonObject_PutInteger(object, "eiid", eiid);

        if (arguments != NULL)
        {
            JsonObject_PutArray(object, "arguments", JsonArray_NewFrom(arguments));
            break;
        }

        if (RET_FAILED(JsonObject_Encode(object, false)))
        {
            LOG_D(TAG, "JsonObject_Encode failed!\n");
            break;
        }

        client = HttpClient_New();
        if (client == NULL)
        {
            LOG_D(TAG, "HttpClient_New failed!\n");
            break;
        }

        exchange = HttpExchange_New("127.0.0.1", port, "PUT", "/event", 3, NULL, 0);
        if (exchange == NULL)
        {
            LOG_D(TAG, "HttpExchange_New failed!\n");
            break;
        }

        if (RET_FAILED(HttpClient_Send(client, exchange)))
        {
            LOG_D(TAG, "HttpClient_Send failed!\n");
            break;
        }

        if (exchange->status != 200)
        {
            LOG_D(TAG, "event occurred failed: %d\n", exchange->status);
            break;
        }

        LOG_D(TAG, "event occurred succeed!\n");
        ret = true;
    } while (false);

    if (client != NULL)
    {
        HttpClient_Delete(client);
    }

    if (exchange != NULL)
    {
        HttpExchange_Delete(exchange);
    }

    if (object != NULL)
    {
        JsonObject_Delete(object);
    }

    return ret;
}

/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Runner.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include <IotLauncher.h>
#include <XcpwsServerRuntime.h>
#include <StringArray.h>
#include "Runner.h"
#include "ModbusDB.h"

#define TAG "Runner"

static IotLauncher * _launcher = NULL;
static Device * _device;
static void init_handlers(HttpRequestHandlers *handlers);

TinyRet Runner_Run(Device *device)
{
    TinyRet ret = TINY_RET_OK;
    HttpRequestHandlers *handlers = NULL;

    RETURN_VAL_IF_FAIL(device, TINY_RET_E_ARG_NULL);

    do
    {
        _device = device;

        handlers = HttpRequestHandlers_New();
        if (handlers == NULL)
        {
            LOG_E(TAG, "HttpRequestHandlers_New FAILED");
            ret = TINY_RET_E_NEW;
            break;
        }

        init_handlers(handlers);

        _launcher = IotLauncher_New();
        if (_launcher == NULL)
        {
            LOG_E(TAG, "IotLauncher_New FAILED");
            ret = TINY_RET_E_NEW;
            break;
        }

        XcpwsServerContext *context = XcpwsServerContext_New(NULL, handlers);
        if (context == NULL)
        {
            LOG_E(TAG, "XcpwsServerContext_New FAILED");
            break;
        }

        ret = IotLauncher_AddRuntime(_launcher, XcpwsServerRuntime_New(context));
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "IotLauncher_AddRuntime FAILED: %d", ret);
            break;
        }

        ret = IotLauncher_Run(_launcher, device);
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "IotLauncher_Run FAILED: %d", ret);
            break;
        }
    } while (false);

    if (_launcher != NULL)
    {
        IotLauncher_Delete(_launcher);
        _launcher = NULL;
    }

    if (handlers != NULL)
    {
        HttpRequestHandlers_Delete(handlers);
    }

    return ret;
}

static HttpMessage* createInternalError(void)
{
    HttpMessage *response = HttpMessage_New();
    if (response != NULL)
    {
        HttpMessage_SetResponse(response, 503, "internal error");
        HttpMessage_SetProtocolIdentifier(response, "HTTP");
        HttpMessage_SetVersion(response, 1, 1);
        HttpHeader_Set(&response->header, "Content-Type", "application/json; charset=utf-8");
        HttpHeader_SetInteger(&response->header, "Content-Length", 0);
    }

    return response;
}

static HttpMessage* onReadModbusDevices (HttpMessage *request, void *ctx)
{
    HttpMessage *response = NULL;
    JsonObject *object = NULL;

    printf("onGetModbusDevices: %s\n", request->request_line.uri);

    do
    {
        object = ModbusDB_GetDevices();
        if (object == NULL)
        {
            break;
        }

        if (RET_FAILED(JsonObject_Encode(object, true)))
        {
            break;
        }

        response = HttpMessage_New();
        if (response == NULL)
        {
            break;
        }

        HttpMessage_SetResponse(response, 200, "OK");
        HttpMessage_SetProtocolIdentifier(response, "HTTP");
        HttpMessage_SetVersion(response, 1, 1);
        HttpMessage_SetContent(response, "application/json; charset=utf-8", object->size, (const uint8_t *)object->string);

    } while (false);

    if (response == NULL)
    {
        response = createInternalError();
    }

    if (object != NULL)
    {
        JsonObject_Delete(object);
    }

    return response;
}

static HttpMessage* onReadModbusDevice (HttpMessage *request, void *ctx)
{
    // /modbus/device/01
    printf("onGetModbusDevice: %s\n", request->request_line.uri);

    HttpMessage *response = NULL;
    JsonObject *object = NULL;

    do
    {
        StringArray * a = StringArray_NewString(request->request_line.uri, "/");
        if (a == NULL)
        {
            break;
        }

        const char *id = TinyList_GetAt(&a->values, a->values.size -1);

        object = ModbusDB_GetDevice(id);
        if (object == NULL)
        {
            break;
        }

        if (RET_FAILED(JsonObject_Encode(object, true)))
        {
            break;
        }

        response = HttpMessage_New();
        if (response == NULL)
        {
            break;
        }

        HttpMessage_SetResponse(response, 200, "OK");
        HttpMessage_SetProtocolIdentifier(response, "HTTP");
        HttpMessage_SetVersion(response, 1, 1);
        HttpMessage_SetContent(response, "application/json; charset=utf-8", object->size, (const uint8_t *)object->string);
    } while (false);

    if (response == NULL)
    {
        response = createInternalError();
    }

    if (object != NULL)
    {
        JsonObject_Delete(object);
    }

    return response;
}

static HttpMessage* onDeleteModbusDevice (HttpMessage *request, void *ctx)
{
    HttpMessage *response = NULL;

    printf("onDeleteModbusDevice: %s\n", request->request_line.uri);

    do
    {
        StringArray * a = StringArray_NewString(request->request_line.uri, "/");
        if (a == NULL)
        {
            break;
        }

        const char *id = TinyList_GetAt(&a->values, a->values.size -1);

        bool deleted = ModbusDB_DeleteDevice(id);

        response = HttpMessage_New();
        if (response == NULL)
        {
            break;
        }

        if (deleted)
        {
            HttpMessage_SetResponse(response, 200, "OK");
        }
        else
        {
            HttpMessage_SetResponse(response, 404, "NOT FOUND");
        }

        HttpMessage_SetProtocolIdentifier(response, "HTTP");
        HttpMessage_SetVersion(response, 1, 1);
    } while (false);

    if (response == NULL)
    {
        response = createInternalError();
    }

    return response;
}

static HttpMessage* onSaveModbusDevice (HttpMessage *request, void *ctx)
{
    HttpMessage *response = NULL;

    printf("onSaveModbusDevice: %s\n", request->request_line.uri);

    do
    {
        StringArray * a = StringArray_NewString(request->request_line.uri, "/");
        if (a == NULL)
        {
            break;
        }

        const char *id = TinyList_GetAt(&a->values, a->values.size -1);

        bool saved = ModbusDB_SaveDevice(id, request->content.buf);

        response = HttpMessage_New();
        if (response == NULL)
        {
            break;
        }

        if (saved)
        {
            HttpMessage_SetResponse(response, 200, "OK");
        }
        else
        {
            HttpMessage_SetResponse(response, 404, "NOT FOUND");
        }

        HttpMessage_SetProtocolIdentifier(response, "HTTP");
        HttpMessage_SetVersion(response, 1, 1);
    } while (false);

    if (response == NULL)
    {
        response = createInternalError();
    }

    return response;
}

static HttpMessage* onReadModbusDefinitions (HttpMessage *request, void *ctx)
{
    HttpMessage *response = NULL;
    JsonObject *object = NULL;

    printf("onGetModbusDefinitions: %s\n", request->request_line.uri);

    do
    {
        object = ModbusDB_GetDefinitions();
        if (object == NULL)
        {
            break;
        }

        if (RET_FAILED(JsonObject_Encode(object, true)))
        {
            break;
        }

        response = HttpMessage_New();
        if (response == NULL)
        {
            break;
        }

        HttpMessage_SetResponse(response, 200, "OK");
        HttpMessage_SetProtocolIdentifier(response, "HTTP");
        HttpMessage_SetVersion(response, 1, 1);
        HttpMessage_SetContent(response, "application/json; charset=utf-8", object->size, (const uint8_t *)object->string);

    } while (false);

    if (response == NULL)
    {
        response = createInternalError();
    }

    if (object != NULL)
    {
        JsonObject_Delete(object);
    }

    return response;
}

static HttpMessage* onReadModbusDefinition (HttpMessage *request, void *ctx)
{
    // /modbus/definitions/01
    printf("onGetModbusDefinition: %s\n", request->request_line.uri);

    HttpMessage *response = NULL;
    JsonObject *object = NULL;

    do
    {
        StringArray * a = StringArray_NewString(request->request_line.uri, "/");
        if (a == NULL)
        {
            break;
        }

        const char *id = TinyList_GetAt(&a->values, a->values.size -1);

        object = ModbusDB_GetDefinition(id);
        if (object == NULL)
        {
            break;
        }

        if (RET_FAILED(JsonObject_Encode(object, true)))
        {
            break;
        }

        response = HttpMessage_New();
        if (response == NULL)
        {
            break;
        }

        HttpMessage_SetResponse(response, 200, "OK");
        HttpMessage_SetProtocolIdentifier(response, "HTTP");
        HttpMessage_SetVersion(response, 1, 1);
        HttpMessage_SetContent(response, "application/json; charset=utf-8", object->size, (const uint8_t *)object->string);
    } while (false);

    if (response == NULL)
    {
        response = createInternalError();
    }

    if (object != NULL)
    {
        JsonObject_Delete(object);
    }

    return response;
}

static HttpMessage* onDeleteModbusDefinition (HttpMessage *request, void *ctx)
{
    HttpMessage *response = NULL;

    printf("onDeleteModbusDevice: %s\n", request->request_line.uri);

    do
    {
        StringArray * a = StringArray_NewString(request->request_line.uri, "/");
        if (a == NULL)
        {
            break;
        }

        const char *id = TinyList_GetAt(&a->values, a->values.size -1);

        bool deleted = ModbusDB_DeleteDefinition(id);

        response = HttpMessage_New();
        if (response == NULL)
        {
            break;
        }

        if (deleted)
        {
            HttpMessage_SetResponse(response, 200, "OK");
        }
        else
        {
            HttpMessage_SetResponse(response, 404, "NOT FOUND");
        }

        HttpMessage_SetProtocolIdentifier(response, "HTTP");
        HttpMessage_SetVersion(response, 1, 1);
    } while (false);

    if (response == NULL)
    {
        response = createInternalError();
    }

    return response;
}

static HttpMessage* onSaveModbusDefinition (HttpMessage *request, void *ctx)
{
    HttpMessage *response = NULL;

    printf("onSaveModbusDefinition: %s\n", request->request_line.uri);

    do
    {
        StringArray * a = StringArray_NewString(request->request_line.uri, "/");
        if (a == NULL)
        {
            break;
        }

        const char *id = TinyList_GetAt(&a->values, a->values.size -1);

        bool saved = ModbusDB_SaveDefinition(id, request->content.buf);

        response = HttpMessage_New();
        if (response == NULL)
        {
            break;
        }

        if (saved)
        {
            HttpMessage_SetResponse(response, 200, "OK");
        }
        else
        {
            HttpMessage_SetResponse(response, 404, "NOT FOUND");
        }

        HttpMessage_SetProtocolIdentifier(response, "HTTP");
        HttpMessage_SetVersion(response, 1, 1);
    } while (false);

    if (response == NULL)
    {
        response = createInternalError();
    }

    return response;
}

static void init_handlers(HttpRequestHandlers *handlers)
{
    HttpRequestHandlers_Put(handlers, "GET", "/modbus/devices", onReadModbusDevices, NULL);
    HttpRequestHandlers_Put(handlers, "GET", "/modbus/device/:id", onReadModbusDevice, NULL);
    HttpRequestHandlers_Put(handlers, "DELETE", "/modbus/device/:id", onDeleteModbusDevice, NULL);
    HttpRequestHandlers_Put(handlers, "PUT", "/modbus/device/:id", onSaveModbusDevice, NULL);

    HttpRequestHandlers_Put(handlers, "GET", "/modbus/definitions", onReadModbusDefinitions, NULL);
    HttpRequestHandlers_Put(handlers, "GET", "/modbus/definition/:id", onReadModbusDefinition, NULL);
    HttpRequestHandlers_Put(handlers, "DELETE", "/modbus/definition/:id", onDeleteModbusDefinition, NULL);
    HttpRequestHandlers_Put(handlers, "PUT", "/modbus/definition/:id", onSaveModbusDefinition, NULL);
}

TinyRet Runner_ChangePropertyValue(PropertyOperation *o)
{
    return Device_TryChangePropertyValue(_device, o);
}

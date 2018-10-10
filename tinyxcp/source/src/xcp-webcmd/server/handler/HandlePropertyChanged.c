/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HandlePropertyChanged.h
 *
 * @remark
 *
 */

#include <XcpMessage.h>
#include <iq/basic/PropertiesChangedFactory.h>
#include <tiny_log.h>
#include <tiny_snprintf.h>
#include "HandlePropertyChanged.h"
#include "HandleCommon.h"
#include "XcpwsClientRuntime.h"

#define TAG  "HandlePropertyChanged"

static void onPropertyChangedResult (XcpMessage *result, void *ctx)
{
    Channel *channel = (Channel *)ctx;

    do
    {
        if (result->iq.type == IQ_TYPE_ERROR)
        {
            sendError(channel, &result->iq.content.error);
            break;
        }

        if (result->iq.content.result.content.propertiesChanged.operations.properties.size != 1)
        {
            sendTextResponse(channel, 501, "RESULT ERROR", "PropertyOperation.size != 1");
            break;
        }

        PropertyOperation *operation = TinyList_GetAt(&result->iq.content.result.content.propertiesChanged.operations.properties, 0);
        if (operation == NULL)
        {
            sendTextResponse(channel, 501, "RESULT ERROR", "Get PropertyOperation failed");
            break;
        }

        if (operation->status != 0)
        {
            char message[256];
            memset(message, 0, 256);
            tiny_snprintf(message, 255, "status: %d", operation->status);
            sendTextResponse(channel, 400, "FAILED: %d", message);
            break;
        }

        sendResponse(channel, 200, "OK");
    } while (false);
}

void HandlePropertyChanged(Channel *channel, HttpContent *content, IotRuntime *runtime)
{
    JsonObject *object = NULL;
    PropertyOperations *operations = NULL;

    do
    {
        if (content->data_size == 0)
        {
            sendTextResponse(channel, 400, "ARGUMENT INVALID", "Content Size is 0");
            break;
        }

        object = JsonObject_NewString(content->buf);
        if (object == NULL)
        {
            sendTextResponse(channel, 400, "ARGUMENT INVALID", "Content invalid");
            break;
        }

        JsonString *did = JsonObject_GetString(object, "did");
        JsonNumber *siid = JsonObject_GetNumber(object, "siid");
        JsonNumber *piid = JsonObject_GetNumber(object, "piid");
        JsonValue *value = JsonObject_GetValue(object, "value");

        if (did == NULL || siid == NULL || piid == NULL || value == NULL)
        {
            sendTextResponse(channel, 400, "ARGUMENT INVALID", "did or siid or piid or value not found");
            break;
        }

        if (siid->type != JSON_NUMBER_INTEGER || piid->type != JSON_NUMBER_INTEGER)
        {
            sendTextResponse(channel, 400, "ARGUMENT INVALID", "siid or piid not integer");
            break;
        }

        operations = PropertyOperations_New();
        if (operations == NULL)
        {
            sendTextResponse(channel, 500, "INTERNAL ERROR", "Out of memory: PropertyOperations_New");
            break;
        }

        PropertyOperation *operation = PropertyOperation_NewValue(did->value, (uint16_t) siid->value.intValue, (uint16_t) piid->value.intValue, value);
        if (operation == NULL)
        {
            sendTextResponse(channel, 500, "INTERNAL ERROR", "Out of memory: PropertyOperation_NewValue");
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&operations->properties, operation)))
        {
            PropertyOperation_Delete(operation);
            sendTextResponse(channel, 500, "INTERNAL ERROR", "Out of memory: TinyList_AddTail");
            break;
        }

        XcpMessage *query = QueryPropertiesChanged_New("", operations);
        if (query == NULL)
        {
            LOG_D(TAG, "QueryPropertiesChanged_New FAILED!");
            sendTextResponse(channel, 500, "INTERNAL ERROR", "Out of memory: QueryPropertiesChanged_New");
            break;
        }

        if (RET_FAILED(XcpwsClientRuntime_SendQuery(runtime, query, onPropertyChangedResult, channel)))
        {
            LOG_D(TAG, "XcpwsClientRuntime_SendQuery FAILED");
            sendTextResponse(channel, 500, "INTERNAL ERROR", "XcpwsClientRuntime_SendQuery");
        }

        XcpMessage_Delete(query);
    } while (false);

    if (object != NULL)
    {
        JsonObject_Delete(object);
    }

    if (operations != NULL)
    {
        // PropertyOperations_Delete(operations);
    }
}
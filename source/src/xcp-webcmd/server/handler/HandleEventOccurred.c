/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HandleEventOccurred.h
 *
 * @remark
 *
 */

#include <XcpMessage.h>
#include <iq/basic/EventOccurredFactory.h>
#include <tiny_log.h>
#include <tiny_snprintf.h>
#include "HandleEventOccurred.h"
#include "HandleCommon.h"
#include "XcpwsClientRuntime.h"

#define TAG  "HandleEventOccurred"

static void onEventOccurredResult (XcpMessage *result, void *ctx)
{
    Channel *channel = (Channel *)ctx;

    do
    {
        if (result->iq.type == IQ_TYPE_ERROR)
        {
            sendError(channel, &result->iq.content.error);
            break;
        }

        sendResponse(channel, 200, "OK");
    } while (false);
}

void HandleEventOccurred(Channel *channel, HttpContent *content, IotRuntime *runtime)
{
    JsonObject *object = NULL;
    EventOperation *operation = NULL;

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
        JsonNumber *eiid = JsonObject_GetNumber(object, "eiid");
        JsonArray *arguments = JsonObject_GetArray(object, "arguments");

        if (did == NULL || siid == NULL || eiid == NULL)
        {
            sendTextResponse(channel, 400, "ARGUMENT INVALID", "did or siid or eiid not found");
            break;
        }

        if (siid->type != JSON_NUMBER_INTEGER || eiid->type != JSON_NUMBER_INTEGER)
        {
            sendTextResponse(channel, 400, "ARGUMENT INVALID", "siid or eiid not integer");
            break;
        }

        operation = EventOperation_New();
        if (operation == NULL)
        {
            sendTextResponse(channel, 500, "INTERNAL ERROR", "EventOperation_New FAILED!");
            break;
        }

        strncpy(operation->eid.did, did->value, DEVICE_ID_LENGTH);
        operation->eid.siid = (uint16_t) siid->value.intValue;
        operation->eid.iid = (uint16_t) eiid->value.intValue;
        if (arguments != NULL)
        {
            operation->arguments = JsonArray_NewFrom(arguments);
            if (operation->arguments == NULL)
            {
                sendTextResponse(channel, 500, "INTERNAL ERROR", "JsonArray_NewFrom FAILED!");
                break;
            }
        }

        XcpMessage *query = QueryEventOccurred_New("", operation);
        if (query == NULL)
        {
            LOG_D(TAG, "QueryEventOccurred_New FAILED!");
            sendTextResponse(channel, 500, "INTERNAL ERROR", "QueryEventOccurred_New FAILED!");
            break;
        }

        if (RET_FAILED(XcpwsClientRuntime_SendQuery(runtime, query, onEventOccurredResult, channel)))
        {
            LOG_D(TAG, "XcpwsClientRuntime_SendQuery FAILED");
            sendTextResponse(channel, 500, "INTERNAL ERROR", "XcpwsClientRuntime_SendQuery FAILED!");
        }

        XcpMessage_Delete(query);
    } while (false);

    if (object != NULL)
    {
        JsonObject_Delete(object);
    }

    if (operation != NULL)
    {
        EventOperation_Delete(operation);
    }
}
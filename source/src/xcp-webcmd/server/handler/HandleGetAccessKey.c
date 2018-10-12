/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HandleGetAccessKey.h
 *
 * @remark
 *
 */

#include <XcpMessage.h>
#include <iq/basic/GetAccessKeyFactory.h>
#include <JsonObject.h>
#include <tiny_log.h>
#include "HandleGetAccessKey.h"
#include "XcpwsClientRuntime.h"
#include "HandleCommon.h"

#define TAG  "HandleGetAccessKey"

static void onGetAccessKeyResult (XcpMessage *result, void *ctx)
{
    Channel *channel = (Channel *)ctx;

    if (result->iq.type == IQ_TYPE_ERROR)
    {
        sendError(channel, &result->iq.content.error);
        return;
    }

    JsonObject *o = JsonObject_New();
    if (o != NULL)
    {
        JsonObject_PutString(o, "key", result->iq.content.result.content.getAccessKey.key);
        sendJsonResponse(channel, 200, "OK", o);
        JsonObject_Delete(o);
    }
}

void HandleGetAccessKey(Channel *channel, IotRuntime *runtime)
{
    do
    {
        XcpMessage *query = QueryGetAccessKey_New("");
        if (query == NULL)
        {
            LOG_D(TAG, "QueryGetAccessKey_New FAILED!");
            break;
        }

        if (RET_FAILED(XcpwsClientRuntime_SendQuery(runtime, query, onGetAccessKeyResult, channel)))
        {
            LOG_D(TAG, "XcpwsClientRuntime_SendQuery FAILED");
        }

        XcpMessage_Delete(query);
    } while (false);
}
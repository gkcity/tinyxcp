/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HandleResetAccessKey.c
 *
 * @remark
 *
 */
#include <XcpMessage.h>
#include <tiny_log.h>
#include <iq/basic/SetAccessKeyFactory.h>
#include "HandleResetAccessKey.h"
#include "XcpwsClientRuntime.h"
#include "HandleCommon.h"

#define TAG  "HandleResetAccessKey"

static void onResetAccessKeyResult (XcpMessage *result, void *ctx)
{
    Channel *channel = (Channel *)ctx;

    do
    {
        if (result->iq.type == IQ_TYPE_ERROR)
        {
            sendError(channel, &result->iq.content.error);
            break;
        }

        sendTextResponse(channel, 200, "OK", NULL);
    } while (false);
}

void HandleResetAccessKey(Channel *channel, IotRuntime *runtime)
{
    do
    {
        XcpMessage *query = QuerySetAccessKey_New("", "helloworldhelloworld");
        if (query == NULL)
        {
            LOG_D(TAG, "QuerySetAccessKey_New FAILED!");
            break;
        }

        if (RET_FAILED(XcpwsClientRuntime_SendQuery(runtime, query, onResetAccessKeyResult, channel)))
        {
            LOG_D(TAG, "XcpwsClientRuntime_SendQuery FAILED");
        }

        XcpMessage_Delete(query);
    } while (false);
}
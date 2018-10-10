/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   ResetAccessKeyHandler.c
 *
 * @remark
 *
 */
#include "HandleResetAccessKey.h"

void onResetAccessKey(Channel *channel, IotRuntime *runtime)
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
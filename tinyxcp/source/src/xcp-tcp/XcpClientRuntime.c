/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpClientRuntime.c
 *
 * @remark
 *
 */

#include "XcpClientRuntime.h"
#include "client/XcpClient.h"
#include <tiny_log.h>
#include <tiny_malloc.h>

#define TAG     "XcpClientRuntime"

TINY_LOR
static TinyRet XcpClientRuntime_Initialize(IotRuntime *thiz)
{
    LOG_D(TAG, "XcpClientRuntime_Initialize");

    return TINY_RET_OK;
}

TINY_LOR
static TinyRet XcpClientRuntime_Destroy(IotRuntime *thiz)
{
    LOG_D(TAG, "XcpClientRuntime_Destroy");

    return TINY_RET_OK;
}

TINY_LOR
static TinyRet XcpClientRuntime_Run(IotRuntime *thiz, Bootstrap *bootstrap, Device *device)
{
    TinyRet ret = TINY_RET_OK;
    Channel *channel = NULL;

    LOG_D(TAG, "XcpClientRuntime_Run");

    do
    {
        device->context = thiz->context;

        channel = XcpClient_New(device, "39.106.31.22", 9001);
//        channel = XcpClient_New(device, "127.0.0.1", 9001);
        if (channel == NULL)
        {
            LOG_D(TAG, "XcpClient_New failed");
            ret = TINY_RET_E_INTERNAL;
            break;
        }

        ret = Bootstrap_AddChannel(bootstrap, channel);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "Bootstrap_AddChannel failed");
            channel->_onRemove(channel);
            break;
        }
    } while (0);

    return ret;
}

TINY_LOR
static TinyRet XcpClientRuntime_Stop(IotRuntime *thiz)
{
    LOG_D(TAG, "XcpClientRuntime_Stop");
    return TINY_RET_OK;
}

TINY_LOR
IotRuntime * XcpClientRuntime_New(void)
{
    IotRuntime * thiz = IotRuntime_New();
    if (thiz != NULL)
    {
        thiz->Name           = "XcpClientRuntime",
        thiz->Initialize     = XcpClientRuntime_Initialize,
        thiz->Destroy        = XcpClientRuntime_Destroy,
        thiz->Run            = XcpClientRuntime_Run,
        thiz->Stop           = XcpClientRuntime_Stop,
        thiz->context        = NULL;
    }

    return thiz;
}
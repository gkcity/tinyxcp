/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpServerRuntime.c
 *
 * @remark
 *
 */

#include "XcpServerRuntime.h"
#include "server/XcpServer.h"
#include <tiny_log.h>
#include <tiny_malloc.h>
#include <server/XcpBonjour.h>

#define TAG     "XcpServerRuntime"

TINY_LOR
TinyRet XcpServerRuntime_Initialize(IotRuntime *thiz)
{
    LOG_D(TAG, "XcpServerRuntime_Initialize");

    return TINY_RET_OK;
}

TINY_LOR
TinyRet XcpServerRuntime_Destroy(IotRuntime *thiz)
{
    LOG_D(TAG, "XcpServerRuntime_Destroy");

    return TINY_RET_OK;
}

TINY_LOR
TinyRet XcpServerRuntime_Run(IotRuntime *thiz, Bootstrap *bootstrap, Device *device)
{
    TinyRet ret = TINY_RET_OK;
    Channel *channel = NULL;
    Channel *mdns = NULL;

    LOG_D(TAG, "XcpServerRuntime_Run");

    do
    {
        device->context = thiz->context;

        channel = XcpServer_New(device);
        if (channel == NULL)
        {
            LOG_E(TAG, "XcpServer_New failed");
            ret = TINY_RET_E_INTERNAL;
            break;
        }

        mdns = XcpBonjour_New(device);
        if (mdns == NULL)
        {
            LOG_E(TAG, "HapBonjour_New failed");
            ret = TINY_RET_E_INTERNAL;
            break;
        }

        ret = Bootstrap_AddChannel(bootstrap, mdns);
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "Bootstrap_AddChannel failed");
            channel->_onRemove(channel);
            mdns->_onRemove(mdns);
            break;
        }

        ret = Bootstrap_AddChannel(bootstrap, channel);
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "Bootstrap_AddChannel failed");
            channel->_onRemove(channel);
            mdns->_onRemove(mdns);
            break;
        }
    } while (0);

    return ret;
}

TINY_LOR
TinyRet XcpServerRuntime_Stop(IotRuntime *thiz)
{
    LOG_D(TAG, "XcpServerRuntime_Stop");
    return TINY_RET_OK;
}

TINY_LOR
IotRuntime * XcpServerRuntime_New(void)
{
    IotRuntime * thiz = IotRuntime_New();
    if (thiz != NULL)
    {
        thiz->Name           = "XcpServerRuntime",
        thiz->Initialize     = XcpServerRuntime_Initialize,
        thiz->Destroy        = XcpServerRuntime_Destroy,
        thiz->Run            = XcpServerRuntime_Run,
        thiz->Stop           = XcpServerRuntime_Stop,
        thiz->context        = NULL;
    }

    return thiz;
}
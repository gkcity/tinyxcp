/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpwsServerRuntime.c
 *
 * @remark
 *
 */

#include <tiny_log.h>
#include <tiny_malloc.h>
#include "XcpwsServerRuntime.h"
#include "server/XcpwsServer.h"
#include "server/XcpwsBonjour.h"


#define TAG     "XcpwsServerRuntime"

TINY_LOR
static TinyRet XcpwsServerRuntime_Initialize(IotRuntime *thiz)
{
    LOG_D(TAG, "XcpwsServerRuntime_Initialize");

    return TINY_RET_OK;
}

TINY_LOR
static TinyRet XcpwsServerRuntime_Destroy(IotRuntime *thiz)
{
    LOG_D(TAG, "XcpwsServerRuntime_Destroy");

    return TINY_RET_OK;
}

TINY_LOR
static TinyRet XcpwsServerRuntime_Run(IotRuntime *thiz, Bootstrap *bootstrap, Device *device)
{
    TinyRet ret = TINY_RET_OK;
    Channel *server = NULL;
    Channel *mdns = NULL;

    LOG_D(TAG, "XcpwsServerRuntime_Run");

    do
    {
        XcpwsServerContext *context = (XcpwsServerContext *)thiz->context;
        context->device = device;

        server = XcpwsServer_New(context);
        if (server == NULL)
        {
            LOG_E(TAG, "XcpwsServer_New failed");
            ret = TINY_RET_E_INTERNAL;
            break;
        }

        mdns = XcpwsBonjour_New(device);
        if (mdns == NULL)
        {
            LOG_E(TAG, "XcpwsBonjour_New failed");
            ret = TINY_RET_E_INTERNAL;
            break;
        }

        ret = Bootstrap_AddChannel(bootstrap, mdns);
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "Bootstrap_AddChannel failed");
            server->_onRemove(server);
            mdns->_onRemove(mdns);
            break;
        }

        ret = Bootstrap_AddChannel(bootstrap, server);
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "Bootstrap_AddChannel failed");
            server->_onRemove(server);
            mdns->_onRemove(mdns);
            break;
        }
    } while (0);

    return ret;
}

TINY_LOR
static TinyRet XcpwsServerRuntime_Stop(IotRuntime *thiz)
{
    LOG_D(TAG, "XcpwsServerRuntime_Stop");
    return TINY_RET_OK;
}

TINY_LOR
IotRuntime * XcpwsServerRuntime_New(XcpwsServerContext *context)
{
    IotRuntime * thiz = IotRuntime_New();
    if (thiz != NULL)
    {
        thiz->Name           = "XcpwsServerRuntime",
        thiz->Initialize     = XcpwsServerRuntime_Initialize,
        thiz->Destroy        = XcpwsServerRuntime_Destroy,
        thiz->Run            = XcpwsServerRuntime_Run,
        thiz->Stop           = XcpwsServerRuntime_Stop,
        thiz->context        = context;
    }

    return thiz;
}
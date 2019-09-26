/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   IotService.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include <IotLauncher.h>
#include <iq/basic/GetAccessKeyFactory.h>
#include <iq/basic/SetAccessKeyFactory.h>
#include "IotService.h"

#define TAG "IotService"

static IotLauncher *_launcher = NULL;
static IotRuntime *_client = NULL;

static void _LoopHook(Bootstrap *thiz, void *ctx)
{
    LOG_D(TAG, "_LoopHook");
}

void IotService_Run(Product *product)
{
    do
    {
        if (_launcher != NULL)
        {
            IotLauncher_Delete(_launcher);
            break;
        }

        _client = XcpwsClientRuntime_New();
        if (_client == NULL)
        {
            LOG_D(TAG, "XcpwsClientRuntime_New FAILED!");
            break;
        }

        _launcher = IotLauncher_NewRuntime(product, _client, _LoopHook, NULL);
        if (_launcher == NULL)
        {
            LOG_D(TAG, "IotLauncher_NewRuntime FAILED!");
            break;
        }

        TinyRet ret = IotLauncher_Run(_launcher);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "IotLauncher_Run FAILED: %d", ret);
            IotLauncher_Delete(_launcher);
        }
    } while (false);
}

void IotService_Stop(void)
{
    if (_launcher != NULL)
    {
        TinyRet ret = IotLauncher_Stop(_launcher);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "IotLauncher_Stop FAILED: %d", ret);
        }
    }
}

void IotService_GetAccessKey(XcpMessageHandler handler, void *ctx)
{
    do
    {
        if (_client == NULL)
        {
            LOG_D(TAG, "Client is NULL!");
            break;
        }

        XcpMessage *query = QueryGetAccessKey_New("");
        if (query == NULL)
        {
            LOG_D(TAG, "QueryGetAccessKey_New FAILED!");
            break;
        }

        if (RET_FAILED(XcpwsClientRuntime_SendQuery(_client, query, handler, ctx)))
        {
            LOG_D(TAG, "XcpwsClientRuntime_SendQuery FAILED");
        }

        XcpMessage_Delete(query);
    } while (false);
}

void IotService_ResetAccessKey(const char *key, XcpMessageHandler handler, void *ctx)
{
    do
    {
        if (_client == NULL)
        {
            LOG_D(TAG, "Client is NULL!");
            break;
        }

        XcpMessage *query = QuerySetAccessKey_New("", key);
        if (query == NULL)
        {
            LOG_D(TAG, "QuerySetAccessKey_New FAILED!");
            break;
        }

        if (RET_FAILED(XcpwsClientRuntime_SendQuery(_client, query, handler, ctx)))
        {
            LOG_D(TAG, "XcpwsClientRuntime_SendQuery FAILED");
        }

        XcpMessage_Delete(query);
    } while (false);
}
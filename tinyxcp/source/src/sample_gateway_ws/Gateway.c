/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Gateway.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include <IotLauncher.h>
#include <XcpwsClientRuntime.h>
#include <XcpwsServerRuntime.h>
#include "Gateway.h"

#define TAG "Gateway"

static IotLauncher * _launcher = NULL;
static Device * _device;

TinyRet Gateway_Run(Device *device)
{
    TinyRet ret = TINY_RET_OK;
	HttpRequestHandlers *handlers = NULL;

    RETURN_VAL_IF_FAIL(device, TINY_RET_E_ARG_NULL);

    do
    {
		handlers = HttpRequestHandlers_New();
		if (handlers == NULL)
		{
			LOG_E(TAG, "HttpRequestHandlers_New FAILED");
			ret = TINY_RET_E_NEW;
			break;
		}

		XcpwsServerContext *context = XcpwsServerContext_New(NULL, handlers);
		if (context == NULL)
		{
			LOG_E(TAG, "XcpwsServerContext_New FAILED");
			break;
		}

        _device = device;

        _launcher = IotLauncher_New();
        if (_launcher == NULL)
        {
            LOG_D(TAG, "IotLauncher_New FAILED");
            ret = TINY_RET_E_NEW;
            break;
        }

#if 0
        ret = IotLauncher_AddRuntime(_launcher, XcpwsClientRuntime_GetInstance());
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "IotLauncher_AddRuntime FAILED: %d", ret);
            break;
        }
#endif

#if 1
        ret = IotLauncher_AddRuntime(_launcher, XcpwsServerRuntime_New(context));
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "IotLauncher_AddRuntime FAILED: %d", ret);
            break;
        }
#endif

        ret = IotLauncher_Run(_launcher, device);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "IotLauncher_Run FAILED: %d", ret);
            break;
        }
    } while (false);

    if (_launcher != NULL)
    {
        for (int i = 0; i < 1000; i++)
        {
            //sleep(1000);
        }

        // IotLauncher_Delete(_launcher);
        _launcher = NULL;
    }

	if (handlers != NULL)
	{
		HttpRequestHandlers_Delete(handlers);
	}

    return ret;
}

TinyRet Gateway_ChangePropertyValue(PropertyOperation *o)
{
    return Device_TryChangePropertyValue(_device, o);
}

//TinyRet Gateway_ResetAccessKey(OnGetAccessKeySucceed onSucceed, OnGetAccessKeyFailed onFailed)
//{
//    return Device_ResetAccessKey(_device, onSucceed, onFailed);
//}
//
//TinyRet Gateway_GetAccessKey(void)
//{
//    return Device_GetAccessKey(_device, NULL);
//}
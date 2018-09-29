/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Runner.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include <IotLauncher.h>
#include <XcpClientRuntime.h>
#include <XcpServerRuntime.h>
#include "Runner.h"

#define TAG "Runner"

static IotLauncher * _launcher = NULL;
static Device * _device;

TinyRet Runner_Run(Device *device)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(device, TINY_RET_E_ARG_NULL);

    do
    {
        _device = device;

        _launcher = IotLauncher_New();
        if (_launcher == NULL)
        {
            LOG_D(TAG, "IotLauncher_New FAILED");
            ret = TINY_RET_E_NEW;
            break;
        }

#if 1
        ret = IotLauncher_AddRuntime(_launcher, XcpClientRuntime_GetInstance());
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "IotLauncher_AddRuntime FAILED: %d", ret);
            break;
        }
#else
        ret = IotLauncher_AddRuntime(_launcher, XcpServerRuntime_GetInstance());
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
        IotLauncher_Delete(_launcher);
        _launcher = NULL;
    }

    return ret;
}

TinyRet Runner_ChangePropertyValue(PropertyOperation *o)
{
    return Device_TryChangePropertyValue(_device, o);
}

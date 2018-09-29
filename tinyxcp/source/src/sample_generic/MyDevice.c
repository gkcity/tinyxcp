/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   MyDevice.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include <IotLauncher.h>
#include <XcpClientRuntime.h>
#include "MyDevice.h"

#define TAG "MyDevice"

static IotLauncher * _launcher = NULL;
static Device * _device;

TinyRet MyDevice_Run(Device *device)
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

        ret = IotLauncher_AddRuntime(_launcher, XcpClientRuntime_GetInstance());
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "IotLauncher_AddRuntime FAILED: %d", ret);
            break;
        }

//        ret = IotLauncher_AddRuntime(_launcher, XcpOnLanRuntime_GetInstance());
//        if (RET_FAILED(ret))
//        {
//            LOG_D(TAG, "IotLauncher_AddRuntime FAILED: %d", ret);
//            break;
//        }

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

TinyRet MyDevice_ChangePropertyValue(PropertyOperation *o)
{
    return Device_TryChangePropertyValue(_device, o);
}

//TinyRet MyDevice_ResetAccessKey(OnGetAccessKeySucceed onSucceed, OnGetAccessKeyFailed onFailed)
//{
//    return Device_ResetAccessKey(_device, onSucceed, onFailed);
//}
//
//TinyRet MyDevice_GetAccessKey(void)
//{
//    return Device_GetAccessKey(_device, NULL);
//}
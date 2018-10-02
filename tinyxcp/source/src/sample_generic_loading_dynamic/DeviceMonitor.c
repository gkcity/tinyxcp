/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   DeviceMonitor.c
*
* @remark
*
*/

#include "DeviceMonitor.h"
#include <TinyThread.h>
#include <tiny_sleep.h>

static void Fan_On_Changed(bool value)
{
//    TinyRet ret = TINY_RET_OK;
//    PropertyOperation *o = PropertyOperation_New();
//
//    strncpy(o->pid.did, DID, DEVICE_ID_LENGTH);
//    o->status = 0;
//    o->pid.siid = 2;
//    o->pid.iid = 1;
//    o->value = JsonValue_NewBoolean(value);
//    if (o->value == NULL)
//    {
//        printf("JsonValue_NewBoolean failed");
//        PropertyOperation_Delete(o);
//        return;
//    }
//
//    ret = DeviceOperator_ChangePropertyValue(o);
//    if (RET_FAILED(ret))
//    {
//        printf("Device_TryChangePropertyValue error: %d", ret);
//    }
//
//    PropertyOperation_Delete(o);
}

//static void reset(void)
//{
//    TinyRet ret = Runner_ResetAccessKey();
//    if (RET_FAILED(ret))
//    {
//        printf("Runner_Reset error: %d", ret);
//    }
//}
//
//static void get_access_key(void)
//{
//    TinyRet ret = Runner_GetAccessKey();
//    if (RET_FAILED(ret))
//    {
//        printf("Runner_GetAccessKey error: %d", ret);
//    }
//}

static TinyThread *_thread = NULL;
static bool _running = true;

static void _loop(void *param)
{
    Device *devie = (Device *) param;

    _running = true;

    while (_running)
    {
        tiny_sleep(1000);
//        printf("monitor...\n");
    }
}

TinyRet StartDeviceMonitor(Device *device)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        if (_thread != NULL)
        {
            ret = TINY_RET_E_STARTED;
            break;
        }

        _thread = TinyThread_New();
        if (_thread == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        ret = TinyThread_Initialize(_thread, _loop, device, "monitor");
        if (RET_FAILED(ret))
        {
            break;
        }

        if (! TinyThread_Start(_thread))
        {
            ret = TINY_RET_E_INTERNAL;
            break;
        }
    } while (false);

    return ret;
}

TinyRet StopDeviceMonitor(void)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        if (_thread == NULL)
        {
            ret = TINY_RET_E_STOPPED;
            break;
        }

        if (_thread->status != ThreadRunning)
        {
            ret = TINY_RET_E_STATUS;
            break;
        }

        _running = false;

        if (!TinyThread_Join(_thread))
        {
            ret = TINY_RET_E_INTERNAL;
        }
    } while (false);

    return ret;
}

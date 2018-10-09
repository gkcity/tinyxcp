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

static TinyThread *_thread = NULL;
static bool _running = true;
static bool _fan_on = true;

static void Fan_On_Changed(Device *device)
{
    _fan_on = ! _fan_on;

    do
    {
        JsonValue * value = JsonValue_NewBoolean(_fan_on);
        if (value == NULL)
        {
            printf("JsonValue_NewBoolean failed");
            break;
        }

        PropertyOperation *o = PropertyOperation_NewValue(device->did, 2, 1, value);
        if (o == NULL)
        {
            printf("PropertyOperation_NewValue failed");
            JsonValue_Delete(value);
            break;
        }

        if (RET_FAILED(Device_TryChangePropertyValue(device, o)))
        {
            PropertyOperation_Delete(o);
            break;
        }

        // send property value to stack by http

        PropertyOperation_Delete(o);
    } while (false);
}

static void _loop(void *param)
{
    Device *device = (Device *) param;

    _running = true;

    while (_running)
    {
        tiny_sleep(1000);
//        Fan_On_Changed(device);
    }
}

TinyRet StartDeviceMonitor(Device *device, uint16_t port)
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

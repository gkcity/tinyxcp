/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   task_iot.c
*
* @remark
*
*/

#include "task_iot.h"
#include "device/IotService.h"
#include <TinyThread.h>
#include <tiny_log.h>

static TinyThread *_thread = NULL;

static void _loop(void *param)
{
    IotService_Run((Product *)param);
}

TinyRet task_iot_start(Product *product)
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

        ret = TinyThread_Initialize(_thread, _loop, product, "task_iot");
        if (RET_FAILED(ret))
        {
            TinyThread_Delete(_thread);
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

TinyRet task_iot_stop(void)
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

        IotService_Stop();

        if (!TinyThread_Join(_thread))
        {
            ret = TINY_RET_E_INTERNAL;
        }
    } while (false);

    return ret;
}
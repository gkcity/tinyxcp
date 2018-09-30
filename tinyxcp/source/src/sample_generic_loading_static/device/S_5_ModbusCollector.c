/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   S_5_ModbusCollector.c
 *
 * @remark
 *
 */

#include "S_5_ModbusCollector.h"
#include "P_5_1_CollectInterval.h"
#include "P_5_2_CollectingStatus.h"
#include "A_5_1_StartCollecting.h"
#include "A_5_2_StopCollecting.h"

Service * S_5_ModbusCollector(void)
{
    Service *thiz = NULL;

    do
    {
        thiz = Service_NewInstance(5, "xiot-spec", "modbus-collector", 0x00007808, NULL);
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_5_1_CollectInterval())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_5_2_CollectingStatus())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->actions, A_5_1_StartCollecting())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->actions, A_5_2_StopCollecting())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}
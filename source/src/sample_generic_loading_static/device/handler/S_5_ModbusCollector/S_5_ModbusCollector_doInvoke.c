/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   S_5_ModbusCollector_doInvoke.c
*
* @remark
*
*/

#include "S_5_ModbusCollector_doInvoke.h"
#include "../../iid/IID.h"

static void A_5_1_StartCollecting_doInvoke(ActionOperation *o)
{
}

static void A_5_2_StopCollecting_doInvoke(ActionOperation *o)
{
}

void S_5_ModbusCollector_doInvoke(ActionOperation *o)
{
    printf("S_5_ModbusCollector_doInvoke: aiid = [%d]\n", o->aid.iid);

    switch (o->aid.iid)
    {
        case IID_5_1_StartCollecting:
            A_5_1_StartCollecting_doInvoke(o);
            break;

        case IID_5_2_StopCollecting:
            A_5_2_StopCollecting_doInvoke(o);
            break;

        default:
            o->status = -100;
            break;
    }
}
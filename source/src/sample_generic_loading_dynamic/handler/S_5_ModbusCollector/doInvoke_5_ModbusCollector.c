/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   doInvoke_5_ModbusCollector.c
*
* @remark
*
*/

#include "doInvoke_5_ModbusCollector.h"
#include "../../iid/IID.h"

static void doInvoke_5_1_StartCollecting(ActionOperation *o)
{

}

static void doInvoke_5_2_StopCollecting(ActionOperation *o)
{

}

void doInvoke_5_ModbusCollector(ActionOperation *o)
{
    switch (o->aid.iid)
    {
        case IID_5_1_StartCollecting:
            doInvoke_5_1_StartCollecting(o);
            break;

        case IID_5_2_StopCollecting:
            doInvoke_5_2_StopCollecting(o);
            break;

        default:
            break;
    }
}
/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   S_5_ModbusCollector_doGet.c
*
* @remark
*
*/

#include "S_5_ModbusCollector_doGet.h"
#include "../../iid/IID.h"

static void P_5_2_CollectingStatus_doGet(PropertyOperation *o)
{
    // o->value = JsonValue_NewString("GeekCity");
}

void S_5_ModbusCollector_doGet(PropertyOperation *o)
{
    printf("S_5_ModbusCollector_doGet: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        case IID_5_2_CollectingStatus:
            P_5_2_CollectingStatus_doGet(o);
            break;

        default:
            o->status = -100;
            break;
    }
}
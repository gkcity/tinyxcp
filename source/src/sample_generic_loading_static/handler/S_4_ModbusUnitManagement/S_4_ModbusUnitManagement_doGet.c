/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   S_4_ModbusUnitManagement_doGet.c
*
* @remark
*
*/

#include "S_4_ModbusUnitManagement_doGet.h"
#include "../../iid/IID.h"

static void P_4_5_UnitCount_doGet(PropertyOperation *o)
{
    // o->value = JsonValue_NewString("GeekCity");
}

void S_4_ModbusUnitManagement_doGet(PropertyOperation *o)
{
    printf("S_4_ModbusUnitManagement_doGet: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        case IID_4_5_UnitCount:
            P_4_5_UnitCount_doGet(o);
            break;

        default:
            o->status = -100;
            break;
    }
}
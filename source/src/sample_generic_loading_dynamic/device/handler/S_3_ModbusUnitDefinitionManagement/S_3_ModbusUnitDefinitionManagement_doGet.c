/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   S_3_ModbusUnitDefinitionManagement_doGet.c
*
* @remark
*
*/

#include "S_3_ModbusUnitDefinitionManagement_doGet.h"
#include "../../iid/IID.h"

static void P_3_5_UnitDefinitionCount_doGet(PropertyOperation *o)
{
    o->value = JsonValue_NewInteger(0);
}

void S_3_ModbusUnitDefinitionManagement_doGet(PropertyOperation *o)
{
    printf("S_3_ModbusUnitDefinitionManagement_doGet: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        case IID_3_5_UnitDefinitionCount:
            P_3_5_UnitDefinitionCount_doGet(o);
            break;

        default:
            o->status = -100;
            break;
    }
}
/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   S_3_ModbusUnitDefinitionManagement_doInvoke.c
*
* @remark
*
*/

#include "S_3_ModbusUnitDefinitionManagement_doInvoke.h"
#include "../../iid/IID.h"

static void A_3_1_AddUnitDefinition_doInvoke(ActionOperation *o)
{
}

static void A_3_2_RemoveUnitDefinition_doInvoke(ActionOperation *o)
{
}

static void A_3_3_ModifyUnitDefinition_doInvoke(ActionOperation *o)
{
}

static void A_3_4_GetUnitDefinition_doInvoke(ActionOperation *o)
{
}

void S_3_ModbusUnitDefinitionManagement_doInvoke(ActionOperation *o)
{
    printf("S_3_ModbusUnitDefinitionManagement_doInvoke: aiid = [%d]\n", o->aid.iid);

    switch (o->aid.iid)
    {
        case IID_3_1_AddUnitDefinition:
            A_3_1_AddUnitDefinition_doInvoke(o);
            break;

        case IID_3_2_RemoveUnitDefinition:
            A_3_2_RemoveUnitDefinition_doInvoke(o);
            break;

        case IID_3_3_ModifyUnitDefinition:
            A_3_3_ModifyUnitDefinition_doInvoke(o);
            break;

        case IID_3_4_GetUnitDefinition:
            A_3_4_GetUnitDefinition_doInvoke(o);
            break;

        default:
            o->status = -100;
            break;
    }
}
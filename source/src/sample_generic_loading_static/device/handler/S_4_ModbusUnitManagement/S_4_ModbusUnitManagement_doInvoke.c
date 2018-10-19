/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   S_4_ModbusUnitManagement_doInvoke.c
*
* @remark
*
*/

#include "S_4_ModbusUnitManagement_doInvoke.h"
#include "../../iid/IID.h"

static void A_4_1_AddUnit_doInvoke(ActionOperation *o)
{
}

static void A_4_2_RemoveUnit_doInvoke(ActionOperation *o)
{
}

static void A_4_3_ModifyUnit_doInvoke(ActionOperation *o)
{
}

static void A_4_4_GetUnit_doInvoke(ActionOperation *o)
{
}

void S_4_ModbusUnitManagement_doInvoke(ActionOperation *o)
{
    printf("S_4_ModbusUnitManagement_doInvoke: aiid = [%d]\n", o->aid.iid);

    switch (o->aid.iid)
    {
        case IID_4_1_AddUnit:
            A_4_1_AddUnit_doInvoke(o);
            break;

        case IID_4_2_RemoveUnit:
            A_4_2_RemoveUnit_doInvoke(o);
            break;

        case IID_4_3_ModifyUnit:
            A_4_3_ModifyUnit_doInvoke(o);
            break;

        case IID_4_4_GetUnit:
            A_4_4_GetUnit_doInvoke(o);
            break;

        default:
            o->status = -100;
            break;
    }
}
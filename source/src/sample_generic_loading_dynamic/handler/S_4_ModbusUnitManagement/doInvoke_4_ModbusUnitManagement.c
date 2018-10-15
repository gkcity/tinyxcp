/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   doInvoke_4_ModbusUnitManagement.c
*
* @remark
*
*/

#include "doInvoke_4_ModbusUnitManagement.h"
#include "../../iid/IID.h"

void doInvoke_4_ModbusUnitManagement(ActionOperation *o)
{
    switch (o->aid.iid)
    {
        case IID_4_1_AddUnit:
            break;

        case IID_4_2_RemoveUnit:
            break;

        case IID_4_3_ModifyUnit:
            break;

        case IID_4_4_GetUnit:
            break;

        default:
            break;
    }
}
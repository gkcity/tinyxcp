/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   doInvoke_3_ModbusUnitDefinitionManagement.c
*
* @remark
*
*/

#include "doInvoke_3_ModbusUnitDefinitionManagement.h"
#include "../../iid/IID.h"

void doInvoke_3_ModbusUnitDefinitionManagement(ActionOperation *o)
{
    switch (o->aid.iid)
    {
        case IID_3_1_AddUnitDefinition:
            break;

        case IID_3_2_RemoveUnitDefinition:
            break;

        case IID_3_3_ModifyUnitDefinition:
            break;

        case IID_3_4_GetUnitDefinition:
            break;

        default:
            break;
    }
}
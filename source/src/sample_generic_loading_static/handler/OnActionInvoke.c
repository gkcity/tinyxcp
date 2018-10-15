/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   OnActionInvoke.c
*
* @remark
*
*/

#include "OnActionInvoke.h"
#include "../iid/IID.h"

void doInvoke_1_DeviceInformation(ActionOperation *o)
{
}

void doInvoke_2_ModbusController(ActionOperation *o)
{
    switch (o->aid.iid)
    {
        case IID_2_1_ReadDiscreteInputs:
            break;

        case IID_2_2_ReadCoils:
            break;

        case IID_2_3_WriteSingleCoil:
            break;

        case IID_2_4_WriteMultipleCoils:
            break;

        case IID_2_5_ReadInputRegisters:
            break;

        case IID_2_6_ReadMultipleHoldingRegisters:
            break;

        case IID_2_7_WriteSingleHoldingRegister:
            break;

        case IID_2_8_WriteMultipleHoldingRegisters:
            break;

        default:
            break;
    }
}

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

void doInvoke_5_ModbusCollector(ActionOperation *o)
{
    switch (o->aid.iid)
    {
        case IID_5_1_StartCollecting:
            break;

        case IID_5_2_StopCollecting:
            break;

        default:
            break;
    }
}

void OnActionInvoke(ActionOperation *o)
{
    printf("OnActionInvoke: did=[%s], siid = [%d], piid = [%d]\n", o->aid.did, o->aid.siid, o->aid.iid);

    switch (o->aid.siid)
    {
        case IID_1_DeviceInformation:
            doInvoke_1_DeviceInformation(o);
            break;

        case IID_2_ModbusController:
            doInvoke_2_ModbusController(o);
            break;

        case IID_3_ModbusUnitDefinitionManagement:
            doInvoke_3_ModbusUnitDefinitionManagement(o);
            break;

        case IID_4_ModbusUnitManagement:
            doInvoke_4_ModbusUnitManagement(o);
            break;

        case IID_5_ModbusCollector:
            doInvoke_5_ModbusCollector(o);
            break;

        default:
            break;
    }
}
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
#include "S_1_DeviceInformation/doInvoke_1_DeviceInformation.h"
#include "S_2_ModbusController/doInvoke_2_ModbusController.h"
#include "S_3_ModbusUnitDefinitionManagement/doInvoke_3_ModbusUnitDefinitionManagement.h"
#include "S_4_ModbusUnitManagement/doInvoke_4_ModbusUnitManagement.h"
#include "S_5_ModbusCollector/doInvoke_5_ModbusCollector.h"

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
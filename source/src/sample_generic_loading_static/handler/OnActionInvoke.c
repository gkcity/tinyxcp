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
#include "S_1_DeviceInformation/S_1_DeviceInformation_doInvoke.h"
#include "S_2_ModbusController/S_2_ModbusController_doInvoke.h"
#include "S_3_ModbusUnitDefinitionManagement/S_3_ModbusUnitDefinitionManagement_doInvoke.h"
#include "S_4_ModbusUnitManagement/S_4_ModbusUnitManagement_doInvoke.h"
#include "S_5_ModbusCollector/S_5_ModbusCollector_doInvoke.h"

void OnActionInvoke(ActionOperation *o)
{
    printf("OnActionInvoke: did=[%s], siid = [%d], piid = [%d]\n", o->aid.did, o->aid.siid, o->aid.iid);

    switch (o->aid.siid)
    {
        case IID_1_DeviceInformation:
            S_1_DeviceInformation_doInvoke(o);
            break;

        case IID_2_ModbusController:
            S_2_ModbusController_doInvoke(o);
            break;

        case IID_3_ModbusUnitDefinitionManagement:
            S_3_ModbusUnitDefinitionManagement_doInvoke(o);
            break;

        case IID_4_ModbusUnitManagement:
            S_4_ModbusUnitManagement_doInvoke(o);
            break;

        case IID_5_ModbusCollector:
            S_5_ModbusCollector_doInvoke(o);
            break;

        default:
            break;
    }
}
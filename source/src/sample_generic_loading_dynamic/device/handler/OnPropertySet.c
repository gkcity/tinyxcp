/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   OnPropertySet.c
*
* @remark
*
*/

#include "OnPropertySet.h"
#include "../iid/IID.h"
#include "../print/PrintValue.h"
#include "S_1_DeviceInformation/S_1_DeviceInformation_doSet.h"
#include "S_2_ModbusController/S_2_ModbusController_doSet.h"
#include "S_3_ModbusUnitDefinitionManagement/S_3_ModbusUnitDefinitionManagement_doSet.h"
#include "S_4_ModbusUnitManagement/S_4_ModbusUnitManagement_doSet.h"
#include "S_5_ModbusCollector/S_5_ModbusCollector_doSet.h"

void OnPropertySet(PropertyOperation *o)
{
    printf("OnPropertySet: did=[%s], siid = [%d], piid = [%d]\n", o->pid.did, o->pid.siid, o->pid.iid);
    printValue(o->value);

    switch (o->pid.siid)
    {
        case IID_1_DeviceInformation:
            S_1_DeviceInformation_doSet(o);
            break;

        case IID_2_ModbusController:
            S_2_ModbusController_doSet(o);
            break;

        case IID_3_ModbusUnitDefinitionManagement:
            S_3_ModbusUnitDefinitionManagement_doSet(o);
            break;

        case IID_4_ModbusUnitManagement:
            S_4_ModbusUnitManagement_doSet(o);
            break;

        case IID_5_ModbusCollector:
            S_5_ModbusCollector_doSet(o);
            break;

        default:
            break;
    }
}
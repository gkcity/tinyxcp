/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   OnPropertyGet.c
*
* @remark
*
*/

#include "OnPropertyGet.h"
#include "../iid/IID.h"
#include "S_1_DeviceInformation/S_1_DeviceInformation_doGet.h"
#include "S_2_ModbusController/S_2_ModbusController_doGet.h"
#include "S_3_ModbusUnitDefinitionManagement/S_3_ModbusUnitDefinitionManagement_doGet.h"
#include "S_4_ModbusUnitManagement/S_4_ModbusUnitManagement_doGet.h"
#include "S_5_ModbusCollector/S_5_ModbusCollector_doGet.h"

void OnPropertyGet(PropertyOperation *o)
{
    printf("OnPropertyGet: did = %s, siid = %d, piid = %d\n", o->pid.did, o->pid.siid, o->pid.iid);

    switch (o->pid.siid)
    {
        case IID_1_DeviceInformation:
            S_1_DeviceInformation_doGet(o);
            break;

        case IID_2_ModbusController:
            S_2_ModbusController_doGet(o);
            break;

        case IID_3_ModbusUnitDefinitionManagement:
            S_3_ModbusUnitDefinitionManagement_doGet(o);
            break;

        case IID_4_ModbusUnitManagement:
            S_4_ModbusUnitManagement_doGet(o);
            break;

        case IID_5_ModbusCollector:
            S_5_ModbusCollector_doGet(o);
            break;

        default:
            break;
    }
}

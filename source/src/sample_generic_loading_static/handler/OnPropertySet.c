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

static void doSet_1_DeviceInformation(PropertyOperation *o)
{
    printf("doSet_1_DeviceInformation: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        default:
            break;
    }
}

static void doSet_2_ModbusController(PropertyOperation *o)
{
    printf("doSet_2_ModbusController: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        default:
            break;
    }
}

static void doSet_3_ModbusUnitDefinitionManagement(PropertyOperation *o)
{
    printf("doSet_3_ModbusUnitDefinitionManagement: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        default:
            break;
    }
}

static void doSet_4_ModbusUnitManagement(PropertyOperation *o)
{
    printf("doSet_4_ModbusUnitManagement: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        default:
            break;
    }
}

static void doSet_5_ModbusCollector(PropertyOperation *o)
{
    printf("doSet_5_ModbusCollector: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        default:
            break;
    }
}

void OnPropertySet(PropertyOperation *o)
{
    printf("OnPropertySet: did=[%s], siid = [%d], piid = [%d]\n", o->pid.did, o->pid.siid, o->pid.iid);
    printValue(o->value);

    switch (o->pid.siid)
    {
        case IID_1_DeviceInformation:
            doSet_1_DeviceInformation(o);
            break;

        case IID_2_ModbusController:
            doSet_2_ModbusController(o);
            break;

        case IID_3_ModbusUnitDefinitionManagement:
            doSet_3_ModbusUnitDefinitionManagement(o);
            break;

        case IID_4_ModbusUnitManagement:
            doSet_4_ModbusUnitManagement(o);
            break;

        case IID_5_ModbusCollector:
            doSet_5_ModbusCollector(o);
            break;

        default:
            break;
    }
}
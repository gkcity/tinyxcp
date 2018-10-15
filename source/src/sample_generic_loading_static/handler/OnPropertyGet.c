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

static void doGet_1_DeviceInformation(PropertyOperation *o)
{
    printf("doGet_1_DeviceInformation: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        case IID_1_1_Manufacturer:
            o->value = JsonValue_NewString("GeekCity");
            break;

        case IID_1_2_Model:
            o->value = JsonValue_NewString("GeekFan2018");
            break;

        case IID_1_3_SerialNumber:
            o->value = JsonValue_NewString("GeekFan");
            break;

        case IID_1_4_FirmwareRevision:
            o->value = JsonValue_NewString("1.0.0");
            break;

        default:
            o->status = -100;
            break;
    }
}

static void doGet_2_ModbusController(PropertyOperation *o)
{
    printf("doGet_2_ModbusController: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        default:
            o->status = -100;
            break;
    }
}

static void doGet_3_ModbusUnitDefinitionManagement(PropertyOperation *o)
{
    printf("doGet_3_ModbusUnitDefinitionManagement: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        case IID_3_5_UnitDefinitionCount:
            o->value = JsonValue_NewInteger(0);
            break;

        default:
            o->status = -100;
            break;
    }
}

static void doGet_4_ModbusUnitManagement(PropertyOperation *o)
{
    printf("doGet_4_ModbusUnitManagement: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        case IID_4_5_UnitCount:
            o->value = JsonValue_NewInteger(0);
            break;

        default:
            o->status = -100;
            break;
    }
}

static void doGet_5_ModbusCollector(PropertyOperation *o)
{
    printf("doGet_5_ModbusCollector: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        case IID_5_2_CollectingStatus:
            o->value = JsonValue_NewInteger(0);
            break;

        default:
            o->status = -100;
            break;
    }
}

void OnPropertyGet(PropertyOperation *o)
{
    printf("OnPropertyGet: did = %s, siid = %d, piid = %d\n", o->pid.did, o->pid.siid, o->pid.iid);

    switch (o->pid.siid)
    {
        case IID_1_DeviceInformation:
            doGet_1_DeviceInformation(o);
            break;

        case IID_2_ModbusController:
            doGet_2_ModbusController(o);
            break;

        case IID_3_ModbusUnitDefinitionManagement:
            doGet_3_ModbusUnitDefinitionManagement(o);
            break;

        case IID_4_ModbusUnitManagement:
            doGet_4_ModbusUnitManagement(o);
            break;

        case IID_5_ModbusCollector:
            doGet_5_ModbusCollector(o);
            break;

        default:
            break;
    }
}

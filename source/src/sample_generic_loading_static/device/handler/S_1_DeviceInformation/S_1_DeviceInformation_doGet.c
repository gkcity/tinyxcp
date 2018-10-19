/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   S_1_DeviceInformation_doGet.c
*
* @remark
*
*/

#include "S_1_DeviceInformation_doGet.h"
#include "../../iid/IID.h"

static void P_1_1_Manufacturer_doGet(PropertyOperation *o)
{
     o->value = JsonValue_NewString("GeekCity");
}

static void P_1_2_Model_doGet(PropertyOperation *o)
{
     o->value = JsonValue_NewString("sample-device");
}

static void P_1_3_SerialNumber_doGet(PropertyOperation *o)
{
     o->value = JsonValue_NewString("10001-1001");
}

static void P_1_4_FirmwareRevision_doGet(PropertyOperation *o)
{
     o->value = JsonValue_NewString("1.0.0");
}

void S_1_DeviceInformation_doGet(PropertyOperation *o)
{
    printf("S_1_DeviceInformation_doGet: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        case IID_1_1_Manufacturer:
            P_1_1_Manufacturer_doGet(o);
            break;

        case IID_1_2_Model:
            P_1_2_Model_doGet(o);
            break;

        case IID_1_3_SerialNumber:
            P_1_3_SerialNumber_doGet(o);
            break;

        case IID_1_4_FirmwareRevision:
            P_1_4_FirmwareRevision_doGet(o);
            break;

        default:
            o->status = -100;
            break;
    }
}
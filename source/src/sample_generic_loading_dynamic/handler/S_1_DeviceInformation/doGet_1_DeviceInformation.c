/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   doGet_1_DeviceInformation.c
*
* @remark
*
*/

#include "doGet_1_DeviceInformation.h"
#include "../../iid/IID.h"


static void doGet_1_1_Manufacturer(PropertyOperation *o)
{
    o->value = JsonValue_NewString("GeekCity");
}

void doGet_1_DeviceInformation(PropertyOperation *o)
{
    printf("doGet_1_DeviceInformation: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        case IID_1_1_Manufacturer:
            doGet_1_1_Manufacturer(o);
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
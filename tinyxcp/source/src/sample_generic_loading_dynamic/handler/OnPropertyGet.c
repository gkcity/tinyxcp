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

static void OnDeviceInformationGet(PropertyOperation *o)
{
    printf("OnDeviceInformationGet: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        case IID_DEVICE_INFORMATION_MANUFACTURER:
            o->value = JsonValue_NewString("GeekCity");
            break;

        case IID_DEVICE_INFORMATION_MODEL:
            o->value = JsonValue_NewString("GeekFan2018");
            break;

        case IID_DEVICE_INFORMATION_NAME:
            o->value = JsonValue_NewString("GeekFan");
            break;

        case IID_DEVICE_INFORMATION_SERIAL_NUMBER:
            o->value = JsonValue_NewString("1234567");
            break;

        case IID_DEVICE_INFORMATION_FIRMWARE_REVISION:
            o->value = JsonValue_NewString("1.0.0");
            break;

        default:
            break;
    }
}

static void OnFanGet(PropertyOperation *o)
{
    printf("OnFanGet: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        case IID_FAN_ON:
            o->value = JsonValue_NewBoolean(false);
            break;

        default:
            break;
    }
}

void OnPropertyGet(PropertyOperation *o)
{
    printf("OnPropertyGet: did = %s, siid = %d, piid = %d\n", o->pid.did, o->pid.siid, o->pid.iid);

    switch (o->pid.siid)
    {
        case IID_DEVICE_INFORMATION:
            OnDeviceInformationGet(o);
            break;

        case IID_FAN:
            OnFanGet(o);
            break;

        default:
            break;
    }
}

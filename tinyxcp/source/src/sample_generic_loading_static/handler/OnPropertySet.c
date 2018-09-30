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

static void OnDeviceInformationSet(PropertyOperation *o)
{
    printf("OnDeviceInformationSet: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        case IID_DEVICE_INFORMATION_IDENTIFY:
            o->status = 0;
            break;

        default:
            break;
    }
}

static void OnFanSet(PropertyOperation *o)
{
    printf("OnFanSet: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        case IID_FAN_ON:
            o->status = 0;
            break;

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
        case IID_DEVICE_INFORMATION:
            OnDeviceInformationSet(o);
            break;

        case IID_FAN:
            OnFanSet(o);
            break;

        default:
            break;
    }
}
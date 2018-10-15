/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   doSet_1_DeviceInformation.c
*
* @remark
*
*/

#include "doSet_1_DeviceInformation.h"
#include "../../iid/IID.h"

void doSet_1_DeviceInformation(PropertyOperation *o)
{
    printf("doSet_1_DeviceInformation: piid = [%d]\n", o->pid.iid);
}
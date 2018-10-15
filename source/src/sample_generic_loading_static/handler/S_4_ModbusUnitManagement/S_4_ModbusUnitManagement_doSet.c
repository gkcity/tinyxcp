/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   S_4_ModbusUnitManagement_doSet.c
*
* @remark
*
*/

#include "S_4_ModbusUnitManagement_doSet.h"
#include "../../iid/IID.h"


void S_4_ModbusUnitManagement_doSet(PropertyOperation *o)
{
    printf("S_4_ModbusUnitManagement_doSet: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        default:
            o->status = -100;
            break;
    }
}
/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   S_5_ModbusCollector_doSet.c
*
* @remark
*
*/

#include "S_5_ModbusCollector_doSet.h"
#include "../../iid/IID.h"


void S_5_ModbusCollector_doSet(PropertyOperation *o)
{
    printf("S_5_ModbusCollector_doSet: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        default:
            o->status = -100;
            break;
    }
}
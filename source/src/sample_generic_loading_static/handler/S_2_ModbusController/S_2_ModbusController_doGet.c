/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   S_2_ModbusController_doGet.c
*
* @remark
*
*/

#include "S_2_ModbusController_doGet.h"
#include "../../iid/IID.h"

void S_2_ModbusController_doGet(PropertyOperation *o)
{
    printf("S_2_ModbusController_doGet: piid = [%d]\n", o->pid.iid);

    switch (o->pid.iid)
    {
        default:
            o->status = -100;
            break;
    }
}
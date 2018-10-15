/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   doInvoke_2_ModbusController.c
*
* @remark
*
*/

#include "doInvoke_2_ModbusController.h"
#include "../../iid/IID.h"

void doInvoke_2_ModbusController(ActionOperation *o)
{
    switch (o->aid.iid)
    {
        case IID_2_1_ReadDiscreteInputs:
            break;

        case IID_2_2_ReadCoils:
            break;

        case IID_2_3_WriteSingleCoil:
            break;

        case IID_2_4_WriteMultipleCoils:
            break;

        case IID_2_5_ReadInputRegisters:
            break;

        case IID_2_6_ReadMultipleHoldingRegisters:
            break;

        case IID_2_7_WriteSingleHoldingRegister:
            break;

        case IID_2_8_WriteMultipleHoldingRegisters:
            break;

        default:
            break;
    }
}
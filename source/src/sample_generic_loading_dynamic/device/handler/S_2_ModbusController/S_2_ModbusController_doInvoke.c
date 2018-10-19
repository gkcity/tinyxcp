/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   S_2_ModbusController_doInvoke.c
*
* @remark
*
*/

#include "S_2_ModbusController_doInvoke.h"
#include "../../iid/IID.h"

static void A_2_1_ReadDiscreteInputs_doInvoke(ActionOperation *o)
{
}

static void A_2_2_ReadCoils_doInvoke(ActionOperation *o)
{
}

static void A_2_3_WriteSingleCoil_doInvoke(ActionOperation *o)
{
}

static void A_2_4_WriteMultipleCoils_doInvoke(ActionOperation *o)
{
}

static void A_2_5_ReadInputRegisters_doInvoke(ActionOperation *o)
{
}

static void A_2_6_ReadMultipleHoldingRegisters_doInvoke(ActionOperation *o)
{
}

static void A_2_7_WriteSingleHoldingRegister_doInvoke(ActionOperation *o)
{
}

static void A_2_8_WriteMultipleHoldingRegisters_doInvoke(ActionOperation *o)
{
}

void S_2_ModbusController_doInvoke(ActionOperation *o)
{
    printf("S_2_ModbusController_doInvoke: aiid = [%d]\n", o->aid.iid);

    switch (o->aid.iid)
    {
        case IID_2_1_ReadDiscreteInputs:
            A_2_1_ReadDiscreteInputs_doInvoke(o);
            break;

        case IID_2_2_ReadCoils:
            A_2_2_ReadCoils_doInvoke(o);
            break;

        case IID_2_3_WriteSingleCoil:
            A_2_3_WriteSingleCoil_doInvoke(o);
            break;

        case IID_2_4_WriteMultipleCoils:
            A_2_4_WriteMultipleCoils_doInvoke(o);
            break;

        case IID_2_5_ReadInputRegisters:
            A_2_5_ReadInputRegisters_doInvoke(o);
            break;

        case IID_2_6_ReadMultipleHoldingRegisters:
            A_2_6_ReadMultipleHoldingRegisters_doInvoke(o);
            break;

        case IID_2_7_WriteSingleHoldingRegister:
            A_2_7_WriteSingleHoldingRegister_doInvoke(o);
            break;

        case IID_2_8_WriteMultipleHoldingRegisters:
            A_2_8_WriteMultipleHoldingRegisters_doInvoke(o);
            break;

        default:
            o->status = -100;
            break;
    }
}
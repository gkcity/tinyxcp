/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   S_2_ModbusController.c
 *
 * @remark
 *
 */

#include "S_2_ModbusController.h"
#include "P_2_1_UnitId.h"
#include "P_2_2_OffsetAddress.h"
#include "P_2_3_NumberOfDiscreteInputs.h"
#include "P_2_4_NumberOfCoils.h"
#include "P_2_5_NumberOfRegisters.h"
#include "P_2_6_NumberOfBytes.h"
#include "P_2_7_CoilValue.h"
#include "P_2_8_CoilValues.h"
#include "P_2_9_DiscreteInputValues.h"
#include "P_2_10_RegisterValues.h"
#include "P_2_11_RegisterValue.h"
#include "A_2_1_ReadDiscreteInputs.h"
#include "A_2_2_ReadCoils.h"
#include "A_2_3_WriteSingleCoil.h"
#include "A_2_4_WriteMultipleCoils.h"
#include "A_2_5_ReadInputRegisters.h"
#include "A_2_6_ReadMultipleHoldingRegisters.h"
#include "A_2_7_WriteSingleHoldingRegister.h"
#include "A_2_8_WriteMultipleHoldingRegisters.h"
#include "E_2_1_InputRegistersChanged.h"

Service * S_2_ModbusController(void)
{
    Service *thiz = NULL;

    do
    {
        thiz = Service_NewInstance(2, "xiot-spec", "modbus-controller", 0x00007808, NULL);
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_2_1_UnitId())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_2_2_OffsetAddress())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_2_3_NumberOfDiscreteInputs())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_2_4_NumberOfCoils())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_2_5_NumberOfRegisters())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_2_6_NumberOfBytes())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_2_7_CoilValue())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_2_8_CoilValues())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_2_9_DiscreteInputValues())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_2_10_RegisterValues())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_2_11_RegisterValue())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->actions, A_2_1_ReadDiscreteInputs())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->actions, A_2_2_ReadCoils())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->actions, A_2_3_WriteSingleCoil())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->actions, A_2_4_WriteMultipleCoils())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->actions, A_2_5_ReadInputRegisters())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->actions, A_2_6_ReadMultipleHoldingRegisters())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->actions, A_2_7_WriteSingleHoldingRegister())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->actions, A_2_8_WriteMultipleHoldingRegisters())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->events, E_2_1_InputRegistersChanged())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}
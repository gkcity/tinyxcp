/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   S_4_ModbusUnitManagement.c
 *
 * @remark
 *
 */

#include "S_4_ModbusUnitManagement.h"
#include "P_4_1_UnitId.h"
#include "P_4_2_UnitName.h"
#include "P_4_3_UnitSerialNumber.h"
#include "P_4_4_UnitDefinitionId.h"
#include "P_4_5_UnitCount.h"
#include "P_4_6_UnitIndex.h"
#include "A_4_1_AddUnit.h"
#include "A_4_2_RemoveUnit.h"
#include "A_4_3_ModifyUnit.h"
#include "A_4_4_GetUnit.h"

Service * S_4_ModbusUnitManagement(void)
{
    Service *thiz = NULL;

    do
    {
        thiz = Service_NewInstance(4, "xiot-spec", "modbus-unit-management", 0x00007808, NULL);
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_4_1_UnitId())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_4_2_UnitName())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_4_3_UnitSerialNumber())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_4_4_UnitDefinitionId())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_4_5_UnitCount())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_4_6_UnitIndex())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->actions, A_4_1_AddUnit())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->actions, A_4_2_RemoveUnit())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->actions, A_4_3_ModifyUnit())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->actions, A_4_4_GetUnit())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}
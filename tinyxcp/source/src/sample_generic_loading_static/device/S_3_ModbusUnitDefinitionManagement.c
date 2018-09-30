/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   S_3_ModbusUnitDefinitionManagement.c
 *
 * @remark
 *
 */

#include "S_3_ModbusUnitDefinitionManagement.h"
#include "P_3_1_UnitDefinitionId.h"
#include "P_3_2_UnitDefinitionName.h"
#include "P_3_3_UnitDefinitionDescription.h"
#include "P_3_4_UnitDefinitionContent.h"
#include "P_3_5_UnitDefinitionCount.h"
#include "P_3_6_UnitDefinitionIndex.h"
#include "A_3_1_AddUnitDefinition.h"
#include "A_3_2_RemoveUnitDefinition.h"
#include "A_3_3_ModifyUnitDefinition.h"
#include "A_3_4_GetUnitDefinition.h"

Service * S_3_ModbusUnitDefinitionManagement(void)
{
    Service *thiz = NULL;

    do
    {
        thiz = Service_NewInstance(3, "xiot-spec", "modbus-unit-definition-management", 0x00007808, NULL);
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_3_1_UnitDefinitionId())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_3_2_UnitDefinitionName())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_3_3_UnitDefinitionDescription())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_3_4_UnitDefinitionContent())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_3_5_UnitDefinitionCount())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_3_6_UnitDefinitionIndex())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->actions, A_3_1_AddUnitDefinition())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->actions, A_3_2_RemoveUnitDefinition())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->actions, A_3_3_ModifyUnitDefinition())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->actions, A_3_4_GetUnitDefinition())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}
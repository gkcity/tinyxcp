/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   A_3_3_ModifyUnitDefinition.c
 *
 * @remark
 *
 */

#include "A_3_3_ModifyUnitDefinition.h"

Action * A_3_3_ModifyUnitDefinition(void)
{
    Action *thiz = NULL;

    do
    {
        thiz = Action_NewInstance(3, "xiot-spec", "modify-unit-definition", 0x0000A001, NULL);
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(Action_InAdd(thiz, 1)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(Action_InAdd(thiz, 2)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(Action_InAdd(thiz, 3)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(Action_InAdd(thiz, 4)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}
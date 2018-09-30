/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   A_3_2_RemoveUnitDefinition.c
 *
 * @remark
 *
 */

#include "A_3_2_RemoveUnitDefinition.h"

Action * A_3_2_RemoveUnitDefinition(void)
{
    Action *thiz = NULL;

    do
    {
        thiz = Action_NewInstance(2, "xiot-spec", "remove-unit-definition", 0x0000A001, NULL);
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
    } while (false);

    return thiz;
}
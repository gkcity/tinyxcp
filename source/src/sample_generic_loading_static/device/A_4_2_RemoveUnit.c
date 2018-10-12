/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   A_4_2_RemoveUnit.c
 *
 * @remark
 *
 */

#include "A_4_2_RemoveUnit.h"

Action * A_4_2_RemoveUnit(void)
{
    Action *thiz = NULL;

    do
    {
        thiz = Action_NewInstance(2, "xiot-spec", "remove-unit", 0x0000A001, NULL);
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
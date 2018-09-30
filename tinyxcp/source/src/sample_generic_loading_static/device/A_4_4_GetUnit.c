/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   A_4_4_GetUnit.c
 *
 * @remark
 *
 */

#include "A_4_4_GetUnit.h"

Action * A_4_4_GetUnit(void)
{
    Action *thiz = NULL;

    do
    {
        thiz = Action_NewInstance(4, "xiot-spec", "get-unit", 0x0000A001, NULL);
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(Action_InAdd(thiz, 6)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(Action_OutAdd(thiz, 1)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(Action_OutAdd(thiz, 2)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(Action_OutAdd(thiz, 3)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(Action_OutAdd(thiz, 4)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}
/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   A_2_4_WriteMultipleCoils.c
 *
 * @remark
 *
 */

#include "A_2_4_WriteMultipleCoils.h"

Action * A_2_4_WriteMultipleCoils(void)
{
    Action *thiz = NULL;

    do
    {
        thiz = Action_NewInstance(4, "xiot-spec", "write-multiple-coils", 0x00000000, NULL);
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

        if (RET_FAILED(Action_InAdd(thiz, 4)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(Action_InAdd(thiz, 6)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(Action_InAdd(thiz, 8)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}
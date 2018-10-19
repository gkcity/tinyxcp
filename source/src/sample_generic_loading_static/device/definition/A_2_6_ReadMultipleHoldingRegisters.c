/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   A_2_6_ReadMultipleHoldingRegisters.c
 *
 * @remark
 *
 */

#include "A_2_6_ReadMultipleHoldingRegisters.h"

Action * A_2_6_ReadMultipleHoldingRegisters(void)
{
    Action *thiz = NULL;

    do
    {
        thiz = Action_NewInstance(6, "xiot-spec", "read-multiple-holding-registers", 0x00000000, NULL);
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

        if (RET_FAILED(Action_InAdd(thiz, 5)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(Action_OutAdd(thiz, 6)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(Action_OutAdd(thiz, 10)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}
/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   A_2_7_WriteSingleHoldingRegister.c
 *
 * @remark
 *
 */

#include "A_2_7_WriteSingleHoldingRegister.h"

Action * A_2_7_WriteSingleHoldingRegister(void)
{
    Action *thiz = NULL;

    do
    {
        thiz = Action_NewInstance(7, "xiot-spec", "write-single-holding-register", 0x00000000, NULL);
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

        if (RET_FAILED(Action_InAdd(thiz, 11)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}
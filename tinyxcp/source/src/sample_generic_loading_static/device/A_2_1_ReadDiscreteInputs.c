/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   A_2_1_ReadDiscreteInputs.c
 *
 * @remark
 *
 */

#include "A_2_1_ReadDiscreteInputs.h"

Action * A_2_1_ReadDiscreteInputs(void)
{
    Action *thiz = NULL;

    do
    {
        thiz = Action_NewInstance(1, "xiot-spec", "read-discrete-inputs", 0x00000000, NULL);
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

        if (RET_FAILED(Action_OutAdd(thiz, 6)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(Action_OutAdd(thiz, 9)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}
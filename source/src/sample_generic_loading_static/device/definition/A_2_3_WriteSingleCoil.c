/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   A_2_3_WriteSingleCoil.c
 *
 * @remark
 *
 */

#include "A_2_3_WriteSingleCoil.h"

Action * A_2_3_WriteSingleCoil(void)
{
    Action *thiz = NULL;

    do
    {
        thiz = Action_NewInstance(3, "xiot-spec", "write-single-coil", 0x00000000, NULL);
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

        if (RET_FAILED(Action_InAdd(thiz, 7)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}
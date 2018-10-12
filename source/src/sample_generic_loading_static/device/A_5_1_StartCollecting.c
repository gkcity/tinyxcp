/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   A_5_1_StartCollecting.c
 *
 * @remark
 *
 */

#include "A_5_1_StartCollecting.h"

Action * A_5_1_StartCollecting(void)
{
    Action *thiz = NULL;

    do
    {
        thiz = Action_NewInstance(1, "xiot-spec", "start-collecting", 0x0000A001, NULL);
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
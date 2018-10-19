/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   A_5_2_StopCollecting.c
 *
 * @remark
 *
 */

#include "A_5_2_StopCollecting.h"

Action * A_5_2_StopCollecting(void)
{
    Action *thiz = NULL;

    do
    {
        thiz = Action_NewInstance(2, "xiot-spec", "stop-collecting", 0x0000A001, NULL);
        if (thiz == NULL)
        {
            break;
        }
    } while (false);

    return thiz;
}
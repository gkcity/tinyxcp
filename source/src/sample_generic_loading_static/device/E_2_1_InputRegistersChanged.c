/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   E_2_1_InputRegistersChanged.c
 *
 * @remark
 *
 */

#include "E_2_1_InputRegistersChanged.h"

Event * E_2_1_InputRegistersChanged(void)
{
    Event *thiz = NULL;

    do
    {
        thiz = Event_NewInstance(1, "xiot-spec", "input-registers-changed", 0x00000000, NULL);
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(Event_ArgumentAdd(thiz, 1)))
        {
            Event_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(Event_ArgumentAdd(thiz, 6)))
        {
            Event_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(Event_ArgumentAdd(thiz, 10)))
        {
            Event_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}
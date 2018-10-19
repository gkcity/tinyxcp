/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_4_5_UnitCount.h
 *
 * @remark
 *
 */

#include "P_4_5_UnitCount.h"

Property * P_4_5_UnitCount(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = Property_NewInstance(5, "xiot-spec", "unit-count", 0x00000000, NULL);
        if (thiz == NULL)
        {
            break;
        }

        thiz->access = ACCESS_READ;
        thiz->format = FORMAT_UINT32;
    } while (false);

    return thiz;
}
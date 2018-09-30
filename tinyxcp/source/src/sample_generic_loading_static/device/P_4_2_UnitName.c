/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_4_2_UnitName.h
 *
 * @remark
 *
 */

#include "P_4_2_UnitName.h"

Property * P_4_2_UnitName(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = Property_NewInstance(2, "xiot-spec", "unit-name", 0x00000000, NULL);
        if (thiz == NULL)
        {
            break;
        }

        thiz->access = ACCESS_READ;
        thiz->format = FORMAT_STRING;
    } while (false);

    return thiz;
}
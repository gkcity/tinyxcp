/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_2_8_CoilValues.h
 *
 * @remark
 *
 */

#include "P_2_8_CoilValues.h"

Property * P_2_8_CoilValues(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = Property_NewInstance(8, "xiot-spec", "coil-values", 0x00000000, NULL);
        if (thiz == NULL)
        {
            break;
        }

        thiz->access = ACCESS_READ;
        thiz->format = FORMAT_STRING;
    } while (false);

    return thiz;
}
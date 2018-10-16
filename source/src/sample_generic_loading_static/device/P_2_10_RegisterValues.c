/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_2_10_RegisterValues.h
 *
 * @remark
 *
 */

#include "P_2_10_RegisterValues.h"

Property * P_2_10_RegisterValues(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = Property_NewInstance(10, "xiot-spec", "register-values", 0x00000000, NULL);
        if (thiz == NULL)
        {
            break;
        }

        thiz->access = 0;
        thiz->format = FORMAT_HEX;
    } while (false);

    return thiz;
}
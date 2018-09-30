/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_1_1_Manufacturer.h
 *
 * @remark
 *
 */

#include "P_1_1_Manufacturer.h"

Property * P_1_1_Manufacturer(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = Property_NewInstance(1, "xiot-spec", "manufacturer", 0x00000001, NULL);
        if (thiz == NULL)
        {
            break;
        }

        thiz->access = ACCESS_READ;
        thiz->format = FORMAT_STRING;
    } while (false);

    return thiz;
}
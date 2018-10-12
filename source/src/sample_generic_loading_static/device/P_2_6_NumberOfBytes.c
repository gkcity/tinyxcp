/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_2_6_NumberOfBytes.h
 *
 * @remark
 *
 */

#include "P_2_6_NumberOfBytes.h"

Property * P_2_6_NumberOfBytes(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = Property_NewInstance(6, "xiot-spec", "number-of-bytes", 0x00000000, NULL);
        if (thiz == NULL)
        {
            break;
        }

        thiz->access = ACCESS_READ;
        thiz->format = FORMAT_STRING;
    } while (false);

    return thiz;
}
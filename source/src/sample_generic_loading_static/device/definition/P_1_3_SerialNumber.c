/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_1_3_SerialNumber.h
 *
 * @remark
 *
 */

#include "P_1_3_SerialNumber.h"

Property * P_1_3_SerialNumber(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = Property_NewInstance(3, "xiot-spec", "serial-number", 0x00000003, NULL);
        if (thiz == NULL)
        {
            break;
        }

        thiz->access = ACCESS_READ;
        thiz->format = FORMAT_STRING;
    } while (false);

    return thiz;
}
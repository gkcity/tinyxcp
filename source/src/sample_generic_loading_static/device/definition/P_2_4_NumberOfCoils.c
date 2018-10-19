/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_2_4_NumberOfCoils.h
 *
 * @remark
 *
 */

#include "P_2_4_NumberOfCoils.h"

Property * P_2_4_NumberOfCoils(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = Property_NewInstance(4, "xiot-spec", "number-of-coils", 0x00000000, NULL);
        if (thiz == NULL)
        {
            break;
        }

        thiz->access = 0;
        thiz->format = FORMAT_UINT16;
    } while (false);

    return thiz;
}
/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_1_2_Model.h
 *
 * @remark
 *
 */

#include "P_1_2_Model.h"

Property * P_1_2_Model(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = Property_NewInstance(2, "xiot-spec", "model", 0x00000002, NULL);
        if (thiz == NULL)
        {
            break;
        }

        thiz->access = ACCESS_READ;
        thiz->format = FORMAT_STRING;
    } while (false);

    return thiz;
}
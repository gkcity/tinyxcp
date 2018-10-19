/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_2_9_DiscreteInputValues.h
 *
 * @remark
 *
 */

#include "P_2_9_DiscreteInputValues.h"

Property * P_2_9_DiscreteInputValues(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = Property_NewInstance(9, "xiot-spec", "discrete-input-values", 0x00000000, NULL);
        if (thiz == NULL)
        {
            break;
        }

        thiz->access = 0;
        thiz->format = FORMAT_HEX;
    } while (false);

    return thiz;
}
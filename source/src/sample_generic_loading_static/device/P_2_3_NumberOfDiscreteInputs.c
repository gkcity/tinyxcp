/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_2_3_NumberOfDiscreteInputs.h
 *
 * @remark
 *
 */

#include "P_2_3_NumberOfDiscreteInputs.h"

Property * P_2_3_NumberOfDiscreteInputs(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = Property_NewInstance(3, "xiot-spec", "number-of-discrete-inputs", 0x00000000, NULL);
        if (thiz == NULL)
        {
            break;
        }

        thiz->access = 0;
        thiz->format = FORMAT_UINT16;
    } while (false);

    return thiz;
}
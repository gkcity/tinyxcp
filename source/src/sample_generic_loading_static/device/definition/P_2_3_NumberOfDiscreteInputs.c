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
    return Property_NewInstance(3, "xiot-spec", "number-of-discrete-inputs", 0x00000000, NULL, FORMAT_UINT16, 0, NONE);
}
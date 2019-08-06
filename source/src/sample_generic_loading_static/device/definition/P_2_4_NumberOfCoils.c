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
    return Property_NewInstance(4, "xiot-spec", "number-of-coils", 0x00000000, NULL, FORMAT_UINT16, 0, NONE);
}
/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_2_8_CoilValues.h
 *
 * @remark
 *
 */

#include "P_2_8_CoilValues.h"

Property * P_2_8_CoilValues(void)
{
    return Property_NewInstance(8, "xiot-spec", "coil-values", 0x00000000, NULL, FORMAT_HEX, 0, NONE);
}
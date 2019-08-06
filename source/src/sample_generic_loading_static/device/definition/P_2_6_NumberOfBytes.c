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
    return Property_NewInstance(6, "xiot-spec", "number-of-bytes", 0x00000000, NULL, FORMAT_UINT8, 0, NONE);
}
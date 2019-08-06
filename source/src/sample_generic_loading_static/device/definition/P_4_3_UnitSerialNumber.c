/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_4_3_UnitSerialNumber.h
 *
 * @remark
 *
 */

#include "P_4_3_UnitSerialNumber.h"

Property * P_4_3_UnitSerialNumber(void)
{
    return Property_NewInstance(3, "xiot-spec", "unit-serial-number", 0x00000000, NULL, FORMAT_UINT32, 0, NONE);
}
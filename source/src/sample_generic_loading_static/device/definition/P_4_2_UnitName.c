/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_4_2_UnitName.h
 *
 * @remark
 *
 */

#include "P_4_2_UnitName.h"

Property * P_4_2_UnitName(void)
{
    return Property_NewInstance(2, "xiot-spec", "unit-name", 0x00000000, NULL, FORMAT_STRING, 0, NONE);
}
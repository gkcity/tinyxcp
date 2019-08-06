/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_4_5_UnitCount.h
 *
 * @remark
 *
 */

#include "P_4_5_UnitCount.h"

Property * P_4_5_UnitCount(void)
{
    return Property_NewInstance(5, "xiot-spec", "unit-count", 0x00000000, NULL, FORMAT_UINT32, ACCESS_READ, NONE);
}
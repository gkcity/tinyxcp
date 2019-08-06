/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_4_6_UnitIndex.h
 *
 * @remark
 *
 */

#include "P_4_6_UnitIndex.h"

Property * P_4_6_UnitIndex(void)
{
    return Property_NewInstance(6, "xiot-spec", "unit-index", 0x00000000, NULL, FORMAT_UINT32, 0, NONE);
}
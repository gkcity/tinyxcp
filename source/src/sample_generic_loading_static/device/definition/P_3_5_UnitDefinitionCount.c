/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_3_5_UnitDefinitionCount.h
 *
 * @remark
 *
 */

#include "P_3_5_UnitDefinitionCount.h"

Property * P_3_5_UnitDefinitionCount(void)
{
    return Property_NewInstance(5, "xiot-spec", "unit-definition-count", 0x00000000, NULL, FORMAT_UINT32, ACCESS_READ, NONE);
}
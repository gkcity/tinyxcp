/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_3_6_UnitDefinitionIndex.h
 *
 * @remark
 *
 */

#include "P_3_6_UnitDefinitionIndex.h"

Property * P_3_6_UnitDefinitionIndex(void)
{
    return Property_NewInstance(6, "xiot-spec", "unit-definition-index", 0x00000000, NULL, FORMAT_UINT32, 0, NONE);
}
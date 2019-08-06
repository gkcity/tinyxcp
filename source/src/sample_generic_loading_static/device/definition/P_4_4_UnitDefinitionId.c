/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_4_4_UnitDefinitionId.h
 *
 * @remark
 *
 */

#include "P_4_4_UnitDefinitionId.h"

Property * P_4_4_UnitDefinitionId(void)
{
    return Property_NewInstance(4, "xiot-spec", "unit-definition-id", 0x00000000, NULL, FORMAT_STRING, 0, NONE);
}
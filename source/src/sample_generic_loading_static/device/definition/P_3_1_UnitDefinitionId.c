/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_3_1_UnitDefinitionId.h
 *
 * @remark
 *
 */

#include "P_3_1_UnitDefinitionId.h"

Property * P_3_1_UnitDefinitionId(void)
{
    return Property_NewInstance(1, "xiot-spec", "unit-definition-id", 0x00000000, NULL, FORMAT_STRING, 0, NONE);
}
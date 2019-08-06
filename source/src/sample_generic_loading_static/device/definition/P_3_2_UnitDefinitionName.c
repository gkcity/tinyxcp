/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_3_2_UnitDefinitionName.h
 *
 * @remark
 *
 */

#include "P_3_2_UnitDefinitionName.h"

Property * P_3_2_UnitDefinitionName(void)
{
    return Property_NewInstance(2, "xiot-spec", "unit-definition-name", 0x00000000, NULL, FORMAT_STRING, 0, NONE);
}
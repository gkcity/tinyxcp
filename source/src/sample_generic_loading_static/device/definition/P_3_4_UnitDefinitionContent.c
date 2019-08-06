/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_3_4_UnitDefinitionContent.h
 *
 * @remark
 *
 */

#include "P_3_4_UnitDefinitionContent.h"

Property * P_3_4_UnitDefinitionContent(void)
{
    return Property_NewInstance(4, "xiot-spec", "unit-definition-content", 0x00000000, NULL, FORMAT_STRING, 0, NONE);
}
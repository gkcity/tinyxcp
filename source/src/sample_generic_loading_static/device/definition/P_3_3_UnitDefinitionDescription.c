/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_3_3_UnitDefinitionDescription.h
 *
 * @remark
 *
 */

#include "P_3_3_UnitDefinitionDescription.h"

Property * P_3_3_UnitDefinitionDescription(void)
{
    return Property_NewInstance(3, "xiot-spec", "unit-definition-description", 0x00000000, NULL, FORMAT_STRING, 0, NONE);
}
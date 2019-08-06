/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_1_1_Manufacturer.h
 *
 * @remark
 *
 */

#include "P_1_1_Manufacturer.h"

Property * P_1_1_Manufacturer(void)
{
    return Property_NewInstance(3, "xiot-spec", "manufacturer", 0x00000001, NULL, FORMAT_STRING, ACCESS_READ, NONE);
}
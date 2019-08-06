/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_2_5_NumberOfRegisters.h
 *
 * @remark
 *
 */

#include "P_2_5_NumberOfRegisters.h"

Property * P_2_5_NumberOfRegisters(void)
{
    return Property_NewInstance(5, "xiot-spec", "number-of-registers", 0x00000000, NULL, FORMAT_UINT16, 0, NONE);
}
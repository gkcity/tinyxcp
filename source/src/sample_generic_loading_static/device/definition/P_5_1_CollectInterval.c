/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_5_1_CollectInterval.h
 *
 * @remark
 *
 */

#include "P_5_1_CollectInterval.h"

Property * P_5_1_CollectInterval(void)
{
    return Property_NewInstance(1, "xiot-spec", "collect-interval", 0x00000000, NULL, FORMAT_UINT32, 0, NONE);
}
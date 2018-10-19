/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   InitializeConfiguration.c
*
* @remark
*
*/

#include "InitializeConfiguration.h"

#define LTSK                "+NC/fa+QFz6hHtcOUKUJK9EQEl/J1nKhh2ixj9hQtGU="
#define LTPK                "V6q8ABMPIOpEyJK/EsdpmsQFtX2+CbpaPMlYOjWNHLE="

void InitializeConfiguration(DeviceConfig *thiz, const char *did, const char *ip)
{
    strncpy(thiz->did, did, DEVICE_ID_LENGTH);
    strncpy(thiz->ip, ip, TINY_IP_LEN);
    strncpy(thiz->ltsk, LTSK, DEVICE_LTSK_BASE64_LENGTH);
    strncpy(thiz->ltpk, LTPK, DEVICE_LTPK_BASE64_LENGTH);
    thiz->productId = PRODUCT_ID;
    thiz->productVersion = PRODUCT_VERSION;
    thiz->port = 0;
}
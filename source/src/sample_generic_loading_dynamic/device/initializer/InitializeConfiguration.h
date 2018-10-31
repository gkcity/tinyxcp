/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   InitializeConfiguration.h
*
* @remark
*
*/

#ifndef __InitializeConfiguration_H__
#define __InitializeConfiguration_H__

#include <device/config/DeviceConfig.h>

TINY_BEGIN_DECLS


#define PRODUCT_ID          10006
#define PRODUCT_VERSION     1

void InitializeConfiguration(DeviceConfig *thiz, const char *serialNumber, const char *ip);


TINY_END_DECLS

#endif /* __InitializeConfiguration_H__ */
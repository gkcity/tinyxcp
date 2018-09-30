/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   DeviceCreator.h
*
* @remark
*
*/

#ifndef __DeviceCreator_H__
#define __DeviceCreator_H__

#include <tiny_base.h>
#include <JsonObject.h>
#include <device/Device.h>

TINY_BEGIN_DECLS


Device* Device_CreateFrom(const char *did, uint16_t productId, uint16_t productVersion, const char *ltsk, const char *file);


TINY_END_DECLS

#endif /* __DeviceCreator_H__ */
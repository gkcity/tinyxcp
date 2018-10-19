/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DeviceInitializer.h
 *
 * @remark
 *
 */

#ifndef __DEVICE_INITIALIZER_H__
#define __DEVICE_INITIALIZER_H__

#include <device/Device.h>

TINY_BEGIN_DECLS


Device *DeviceInitialize(const char *did, const char *ip);


TINY_END_DECLS


#endif /* __DEVICE_INITIALIZER_H__ */

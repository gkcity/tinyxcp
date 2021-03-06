/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   DeviceStack.h
*
* @remark
*
*/

#ifndef __DeviceStack_H__
#define __DeviceStack_H__

#include <product/Product.h>

TINY_BEGIN_DECLS


TinyRet StartDeviceStack(Product *product, uint16_t *port);

TinyRet StopDeviceStack(void);


TINY_END_DECLS

#endif /* __DeviceStack_H__ */
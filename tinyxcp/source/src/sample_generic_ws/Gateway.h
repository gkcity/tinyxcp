/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   MyDevice.h
*
* @remark
*
*/

#ifndef __MyDevice_H__
#define __MyDevice_H__

#include <tiny_base.h>
#include <device/Device.h>

TINY_BEGIN_DECLS


TinyRet MyDevice_Run(Device *device);
TinyRet MyDevice_ChangePropertyValue(PropertyOperation *o);
//TinyRet MyDevice_ResetAccessKey(OnGetAccessKeySucceed onSucceed, OnGetAccessKeyFailed onFailed);
//TinyRet MyDevice_GetAccessKey(void);


TINY_END_DECLS

#endif /* __MyDevice_H__ */
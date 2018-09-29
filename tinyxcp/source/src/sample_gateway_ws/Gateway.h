/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   Gateway.h
*
* @remark
*
*/

#ifndef __Gateway_H__
#define __Gateway_H__

#include <tiny_base.h>
#include <device/Device.h>

TINY_BEGIN_DECLS


TinyRet Gateway_Run(Device *device);
TinyRet Gateway_ChangePropertyValue(PropertyOperation *o);
//TinyRet Gateway_ResetAccessKey(OnGetAccessKeySucceed onSucceed, OnGetAccessKeyFailed onFailed);
//TinyRet Gateway_GetAccessKey(void);


TINY_END_DECLS

#endif /* __Gateway_H__ */
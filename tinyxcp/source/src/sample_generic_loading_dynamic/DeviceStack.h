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

#include <device/Device.h>

TINY_BEGIN_DECLS


TinyRet StartDeviceStack(Device *device);

TinyRet StopDeviceStack(void);

//TinyRet DeviceOperator_Run(Device *device);
//TinyRet DeviceOperator_ChangePropertyValue(PropertyOperation *o);
//TinyRet Runner_ResetAccessKey(OnGetAccessKeySucceed onSucceed, OnGetAccessKeyFailed onFailed);
//TinyRet Runner_GetAccessKey(void);


TINY_END_DECLS

#endif /* __DeviceStack_H__ */
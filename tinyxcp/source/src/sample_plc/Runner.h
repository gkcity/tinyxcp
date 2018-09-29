/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   Runner.h
*
* @remark
*
*/

#ifndef __Runner_H__
#define __Runner_H__

#include <tiny_base.h>
#include <device/Device.h>

TINY_BEGIN_DECLS


TinyRet Runner_Run(Device *device);
TinyRet Runner_ChangePropertyValue(PropertyOperation *o);


TINY_END_DECLS

#endif /* __Runner_H__ */
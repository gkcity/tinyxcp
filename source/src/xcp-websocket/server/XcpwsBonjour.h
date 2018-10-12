/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpwsBonjour.h
 *
 * @remark
 *
 */

#ifndef __XCP_WS_BONJOUR_H__
#define __XCP_WS_BONJOUR_H__

#include <channel/Channel.h>
#include <device/Device.h>

TINY_BEGIN_DECLS


TINY_LOR
Channel * XcpwsBonjour_New(Device *device);


TINY_END_DECLS

#endif /* __XCP_WS_BONJOUR_H__ */
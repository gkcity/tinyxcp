/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcmdClientHandler.h
 *
 * @remark
 *
 */


#ifndef __XCMD_CLIENT_HANDLER_H__
#define __XCMD_CLIENT_HANDLER_H__

#include <tiny_base.h>
#include <channel/ChannelHandler.h>
#include <device/Device.h>

TINY_BEGIN_DECLS


#define XcmdClientHandler_Name  "XcmdClientHandler"

TINY_LOR
ChannelHandler * XcmdClientHandler(Device *device);


TINY_END_DECLS

#endif /* __XCMD_CLIENT_HANDLER_H__ */
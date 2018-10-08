/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcmdServerHandler.h
 *
 * @remark
 *
 */


#ifndef __XCMD_SERVER_HANDLER_H__
#define __XCMD_SERVER_HANDLER_H__

#include <tiny_base.h>
#include <channel/ChannelHandler.h>
#include <device/Device.h>

TINY_BEGIN_DECLS


#define XcmdServerHandler_Name  "XcmdServerHandler"

TINY_LOR
ChannelHandler * XcmdServerHandler(void);


TINY_END_DECLS

#endif /* __XCMD_SERVER_HANDLER_H__ */
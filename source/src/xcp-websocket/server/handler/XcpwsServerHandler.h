/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpwsServerHandler.h
 *
 * @remark
 *
 */


#ifndef __XCP_WS_SERVER_HANDLER_H__
#define __XCP_WS_SERVER_HANDLER_H__

#include <tiny_base.h>
#include <channel/ChannelHandler.h>
#include <device/Device.h>
#include <server/XcpwsServerContext.h>

TINY_BEGIN_DECLS


#define XcpwsServerHandler_Name  "XcpwsServerHandler"

TINY_LOR
ChannelHandler * XcpwsServerHandler(XcpwsServerContext *context);


TINY_END_DECLS

#endif /* __XCP_WS_SERVER_HANDLER_H__ */
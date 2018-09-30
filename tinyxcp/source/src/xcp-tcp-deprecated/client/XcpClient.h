/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpClient.h
 *
 * @remark
 *
 */

#ifndef __XCP_CLIENT_H__
#define __XCP_CLIENT_H__

#include <device/Device.h>
#include <channel/Channel.h>
#include <XcpMessage.h>
#include <handler/XcpMessageHandlerWrapper.h>

TINY_BEGIN_DECLS


TINY_LOR
Channel * XcpClient_New(Device *device, const char *ip, uint16_t port);


TINY_LOR
TinyRet XcpClient_SendQuery(Channel *thiz, XcpMessage *query, XcpMessageHandler handler, void *ctx);



TINY_END_DECLS

#endif /* __XCP_CLIENT_H__ */
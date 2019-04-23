/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpwsClient.h
 *
 * @remark
 *
 */

#ifndef __XCP_WS_CLIENT_H__
#define __XCP_WS_CLIENT_H__

#include <product/Product.h>
#include <channel/Channel.h>
#include <XcpMessage.h>
#include <handler/XcpMessageHandler.h>

TINY_BEGIN_DECLS


TINY_LOR
Channel * XcpwsClient_New(Product *product, const char *ip, uint16_t port);

TINY_LOR
TinyRet XcpwsClient_SendQuery(Channel *thiz, XcpMessage *query, XcpMessageHandler handler, void *ctx);


TINY_END_DECLS

#endif /* __XCP_WS_CLIENT_H__ */
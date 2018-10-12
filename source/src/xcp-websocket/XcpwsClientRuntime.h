/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpwsClientRuntime.h
 *
 * @remark
 *
 */

#ifndef __XCP_CLIENT_RUNTIME_H__
#define __XCP_CLIENT_RUNTIME_H__

#include <IotRuntime.h>
#include <XcpMessage.h>
#include <handler/XcpMessageHandler.h>

TINY_BEGIN_DECLS


TINY_LOR
IotRuntime * XcpwsClientRuntime_New(void);

TINY_LOR
TinyRet XcpwsClientRuntime_SendQuery(IotRuntime *thiz, XcpMessage *query, XcpMessageHandler handler, void *ctx);


TINY_END_DECLS

#endif /* __XCP_CLIENT_RUNTIME_H__ */
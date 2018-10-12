/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpwsServerRuntime.h
 *
 * @remark
 *
 */

#ifndef __XCP_WS_SERVER_RUNTIME_H__
#define __XCP_WS_SERVER_RUNTIME_H__

#include <IotRuntime.h>
#include <server/XcpwsServerContext.h>

TINY_BEGIN_DECLS


TINY_LOR
IotRuntime * XcpwsServerRuntime_New(XcpwsServerContext *context);



TINY_END_DECLS

#endif /* __XCP_WS_SERVER_RUNTIME_H__ */
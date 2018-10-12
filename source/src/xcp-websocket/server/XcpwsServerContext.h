/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpwsServerContext.h
 *
 * @remark
 *
 */

#ifndef __XCP_WS_SERVER_CONTEXT_H__
#define __XCP_WS_SERVER_CONTEXT_H__

#include <device/Device.h>
#include <handler/HttpRequestHandlers.h>

TINY_BEGIN_DECLS


typedef struct _XcpwsServerContext
{
    Device *device;
    HttpRequestHandlers *handlers;
} XcpwsServerContext;


TINY_LOR
XcpwsServerContext * XcpwsServerContext_New(Device *device, HttpRequestHandlers *handlers);

TINY_LOR
void XcpwsServerContext_Delete(XcpwsServerContext *thiz);


TINY_END_DECLS

#endif /* __XCP_WS_SERVER_CONTEXT_H__ */
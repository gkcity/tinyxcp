/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpwsServerHandlerContext.h
 *
 * @remark
 *
 */

#ifndef __XCP_WS_SERVER_HANDLER_CONTEXT_H__
#define __XCP_WS_SERVER_HANDLER_CONTEXT_H__

#include <tiny_base.h>
#include <TinyMap.h>
#include <channel/ChannelHandler.h>
#include <device/Device.h>
#include <XcpMessage.h>
#include <handler/XcpMessageHandler.h>
#include <server/XcpwsServerContext.h>

TINY_BEGIN_DECLS


typedef struct _XcpwsServerHandlerContext
{
    uint32_t                  messageIndex;
    char                      messageId[MESSAGE_ID_LENGTH];
    TinyMap                   handlers;
    XcpwsServerContext      * data;
    Channel                 * channel;
} XcpwsServerHandlerContext;

TINY_LOR
XcpwsServerHandlerContext * XcpwsServerHandlerContext_New(XcpwsServerContext *data);

TINY_LOR
void XcpwsServerHandlerContext_Delete(XcpwsServerHandlerContext *thiz);

TINY_LOR
TinyRet XcpwsServerHandlerContext_AddHandler(XcpwsServerHandlerContext *thiz, const char *id, XcpMessageHandler handler, void *ctx);

TINY_LOR
TinyRet XcpwsServerHandlerContext_Handle(XcpwsServerHandlerContext *thiz, XcpMessage *message);

TINY_LOR
const char *XcpwsServerHandlerContext_NextId(XcpwsServerHandlerContext *thiz);


TINY_END_DECLS

#endif /* __XCP_WS_SERVER_HANDLER_CONTEXT_H__ */
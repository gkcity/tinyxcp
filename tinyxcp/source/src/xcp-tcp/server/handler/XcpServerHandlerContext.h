/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpServerHandlerContext.h
 *
 * @remark
 *
 */

#ifndef __XCP_CLIENT_HANDLER_CONTEXT_H__
#define __XCP_CLIENT_HANDLER_CONTEXT_H__

#include <tiny_base.h>
#include <TinyMap.h>
#include <channel/ChannelHandler.h>
#include <device/Device.h>
#include <XcpMessage.h>
#include <handler/XcpMessageHandlerWrapper.h>

TINY_BEGIN_DECLS


typedef struct _XcpServerHandlerContext
{
    uint32_t                  messageIndex;
    char                      messageId[MESSAGE_ID_LENGTH];
    TinyMap                   handlers;
    Device                  * device;
    Channel                 * channel;
} XcpServerHandlerContext;

TINY_LOR
XcpServerHandlerContext * XcpServerHandlerContext_New(Device *device);

TINY_LOR
void XcpServerHandlerContext_Delete(XcpServerHandlerContext *thiz);

TINY_LOR
TinyRet XcpServerHandlerContext_AddHandler(XcpServerHandlerContext *thiz, const char *id, XcpMessageHandler handler, void *ctx);

TINY_LOR
TinyRet XcpServerHandlerContext_Handle(XcpServerHandlerContext *thiz, XcpMessage *message);

TINY_LOR
const char *XcpServerHandlerContext_NextId(XcpServerHandlerContext *thiz);


TINY_END_DECLS

#endif /* __XCP_CLIENT_HANDLER_CONTEXT_H__ */
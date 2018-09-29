/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpClientHandlerContext.h
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
#include <handler/XcpMessageHandlerWrapper.h>
#include <XcpMessage.h>
#include "XcpStage.h"
#include "XcpClientVerifier.h"


TINY_BEGIN_DECLS


typedef struct _XcpClientHandlerContext
{
    uint32_t                  messageIndex;
    char                      messageId[MESSAGE_ID_LENGTH];
    TinyMap                   handlers;
    Device                  * device;
    XcpClientVerifier       * verifier;
    Channel                 * channel;
} XcpClientHandlerContext;

TINY_LOR
XcpClientHandlerContext * XcpClientHandlerContext_New(Device *device);

TINY_LOR
void XcpClientHandlerContext_Delete(XcpClientHandlerContext *thiz);

TINY_LOR
TinyRet XcpClientHandlerContext_AddHandler(XcpClientHandlerContext *thiz, const char *id, XcpMessageHandler handler, void *ctx);

TINY_LOR
TinyRet XcpClientHandlerContext_Handle(XcpClientHandlerContext *thiz, XcpMessage *message);

TINY_LOR
const char *XcpClientHandlerContext_NextId(void *context);

TINY_LOR
TinyRet XcpClientHandlerContext_SendQuery(void *context, XcpMessage *query, XcpMessageHandler handler, void *ctx);


TINY_END_DECLS

#endif /* __XCP_CLIENT_HANDLER_CONTEXT_H__ */

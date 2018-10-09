/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpwsClientHandlerContext.h
 *
 * @remark
 *
 */

#ifndef __XCP_WS_CLIENT_HANDLER_CONTEXT_H__
#define __XCP_WS_CLIENT_HANDLER_CONTEXT_H__

#include <tiny_base.h>
#include <TinyMap.h>
#include <channel/ChannelHandler.h>
#include <device/Device.h>
#include <XcpMessage.h>
#include "XcpStage.h"
#include "client/verifier/XcpClientVerifier.h"
#include "handler/XcpMessageHandler.h"

TINY_BEGIN_DECLS


typedef struct _XcpwsClientHandlerContext
{
    uint32_t                  messageIndex;
    TinyMap                   handlers;
    Device                  * device;
    XcpClientVerifier       * verifier;
    Channel                 * channel;
} XcpwsClientHandlerContext;

TINY_LOR
XcpwsClientHandlerContext * XcpwsClientHandlerContext_New(Device *device);

TINY_LOR
void XcpwsClientHandlerContext_Delete(XcpwsClientHandlerContext *thiz);

TINY_LOR
TinyRet XcpwsClientHandlerContext_AddHandler(XcpwsClientHandlerContext *thiz, const char *id, XcpMessageHandler handler, void *ctx);

TINY_LOR
TinyRet XcpwsClientHandlerContext_Handle(XcpwsClientHandlerContext *thiz, XcpMessage *message);

TINY_LOR
TinyRet XcpwsClientHandlerContext_SendQuery(void *context, XcpMessage *query, XcpMessageHandler handler, void *ctx);


TINY_END_DECLS

#endif /* __XCP_WS_CLIENT_HANDLER_CONTEXT_H__ */

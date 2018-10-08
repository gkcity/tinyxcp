/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcmdClientHandlerContext.h
 *
 * @remark
 *
 */

#ifndef __XCMD_CLIENT_HANDLER_CONTEXT_H__
#define __XCMD_CLIENT_HANDLER_CONTEXT_H__

#include <tiny_base.h>
#include <TinyMap.h>
#include <channel/ChannelHandler.h>
#include <device/Device.h>
#include <XcpMessage.h>
#include "XcpStage.h"
#include "XcpClientVerifier.h"
#include "handler/XcpMessageHandlerWrapper.h"

TINY_BEGIN_DECLS


typedef struct _XcmdClientHandlerContext
{
    uint32_t                  messageIndex;
    char                      messageId[MESSAGE_ID_LENGTH];
    TinyMap                   handlers;
    Device                  * device;
    XcpClientVerifier       * verifier;
    Channel                 * channel;
} XcmdClientHandlerContext;

TINY_LOR
XcmdClientHandlerContext * XcmdClientHandlerContext_New(Device *device);

TINY_LOR
void XcmdClientHandlerContext_Delete(XcmdClientHandlerContext *thiz);

TINY_LOR
TinyRet XcmdClientHandlerContext_AddHandler(XcmdClientHandlerContext *thiz, const char *id, XcpMessageHandler handler, void *ctx);

TINY_LOR
TinyRet XcmdClientHandlerContext_Handle(XcmdClientHandlerContext *thiz, XcpMessage *message);

TINY_LOR
const char *XcmdClientHandlerContext_NextId(void *context);

TINY_LOR
TinyRet XcpClientHandlerContext_SendQuery(void *context, XcpMessage *query, XcpMessageHandler handler, void *ctx);


TINY_END_DECLS

#endif /* __XCMD_CLIENT_HANDLER_CONTEXT_H__ */

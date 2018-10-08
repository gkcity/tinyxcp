/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcmdServerHandlerContext.h
 *
 * @remark
 *
 */

#ifndef __XCMD_SERVER_HANDLER_CONTEXT_H__
#define __XCMD_SERVER_HANDLER_CONTEXT_H__

#include <tiny_base.h>
#include <TinyMap.h>
#include <channel/ChannelHandler.h>
#include <device/Device.h>
#include <XcpMessage.h>
#include <handler/XcpMessageHandlerWrapper.h>

TINY_BEGIN_DECLS


typedef struct _XcmdServerHandlerContext
{
    uint32_t                  messageIndex;
    char                      messageId[MESSAGE_ID_LENGTH];
    TinyMap                   handlers;
    Channel                 * channel;
} XcmdServerHandlerContext;

TINY_LOR
XcmdServerHandlerContext * XcmdServerHandlerContext_New(void);

TINY_LOR
void XcmdServerHandlerContext_Delete(XcmdServerHandlerContext *thiz);

TINY_LOR
TinyRet XcmdServerHandlerContext_AddHandler(XcmdServerHandlerContext *thiz, const char *id, XcpMessageHandler handler, void *ctx);

TINY_LOR
TinyRet XcmdServerHandlerContext_Handle(XcmdServerHandlerContext *thiz, XcpMessage *message);

TINY_LOR
const char *XcmdServerHandlerContext_NextId(XcmdServerHandlerContext *thiz);


TINY_END_DECLS

#endif /* __XCMD_SERVER_HANDLER_CONTEXT_H__ */
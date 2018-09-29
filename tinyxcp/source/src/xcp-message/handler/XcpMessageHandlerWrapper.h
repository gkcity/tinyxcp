/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpMessageHandlerWrapper.h
 *
 * @remark
 *
 */

#ifndef __XCP_MESSAGE_HANDLER_WRAPPER_H__
#define __XCP_MESSAGE_HANDLER_WRAPPER_H__

#include <tiny_base.h>
#include <XcpMessage.h>

TINY_BEGIN_DECLS


typedef void(*XcpMessageHandler) (XcpMessage * message, void *ctx);

typedef struct _XcpMessageHandlerWrapper
{
    XcpMessageHandler         handler;
    void                    * ctx;
} XcpMessageHandlerWrapper;

TINY_LOR
XcpMessageHandlerWrapper * XcpMessageHandlerWrapper_New(XcpMessageHandler handler, void *ctx);

TINY_LOR
void XcpMessageHandlerWrapper_Delete(XcpMessageHandlerWrapper *thiz);


TINY_END_DECLS

#endif /* __XCP_MESSAGE_HANDLER_WRAPPER_H__ */
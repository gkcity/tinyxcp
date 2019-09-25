/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpwsServer.c
 *
 * @remark
 *
 */

#include <channel/SocketChannel.h>
#include <channel/ChannelIdleStateHandler.h>
#include <channel/stream/StreamServerChannel.h>
#include <channel/stream/StreamServerChannelContext.h>
#include <codec-http/HttpMessageCodec.h>
#include <server/handler/XcpwsServerHandler.h>
#include <server/hook/XcpwsServerLoopHook.h>
#include <tiny_log.h>
#include "XcpwsServer.h"

#define TAG     "XcpwsServer"

TINY_LOR
static void XcpwsServerInitializer(Channel *channel, void *ctx)
{
    LOG_D(TAG, "XcpwsServerInitializer: %s", channel->id);
    SocketChannel_AddLast(channel, ChannelIdleStateHandler(0, 0, XCP_CONNECTION_TIMEOUT));
    SocketChannel_AddLast(channel, HttpMessageCodec());
    SocketChannel_AddLast(channel, XcpwsServerHandler((XcpwsServerContext *)ctx));
}

TINY_LOR
Channel * XcpwsServer_New(XcpwsServerContext *context)
{
    Channel *thiz = NULL;

    do
    {
        thiz = StreamServerChannel_New(XCP_MAX_CONNECTIONS, XcpwsServerLoopHook, context);
        if (thiz == NULL)
        {
            break;
        }

        StreamServerChannel_Initialize(thiz, XcpwsServerInitializer, context);

        if (RET_FAILED(SocketChannel_Open(thiz, TYPE_TCP_SERVER)))
        {
            LOG_D(TAG, "SocketChannel_Open failed");
            thiz->_onRemove(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(SocketChannel_Bind(thiz, context->product->config.port, false)))
        {
            LOG_D(TAG, "SocketChannel_Bind failed");
            thiz->_onRemove(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(SocketChannel_SetBlock(thiz, false)))
        {
            LOG_D(TAG, "SocketChannel_SetBlock failed");
            thiz->_onRemove(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(SocketChannel_Listen(thiz, ((StreamServerChannelContext *) thiz->context)->maxConnections)))
        {
            LOG_D(TAG, "SocketChannel_Listen failed");
            thiz->_onRemove(thiz);
            thiz = NULL;
            break;
        }

        if (context->product->config.port == 0)
        {
            context->product->config.port = thiz->local.socket.port;
        }
    } while (false);

    return thiz;
}

//TINY_LOR
//TinyRet XcpwsServer_SendQuery(IQ *query, IQ *result, XcpResultHandler handler, void *ctx)
//{
//    SocketChannel_StartWrite(channel, DATA_XCP_MESSAGE, message, 0);
//}
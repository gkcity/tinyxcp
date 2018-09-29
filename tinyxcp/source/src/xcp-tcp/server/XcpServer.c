/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpServer.c
 *
 * @remark
 *
 */

#include <channel/SocketChannel.h>
#include <channel/ChannelIdleStateHandler.h>
#include <channel/stream/StreamServerChannel.h>
#include <channel/stream/StreamServerChannelContext.h>
#include <codec-message/MessageCodec.h>
#include <server/handler/XcpServerHandler.h>
#include <tiny_log.h>
#include "XcpServer.h"

#define TAG     "XcpServer"

TINY_LOR
static void XcpServerInitializer(Channel *channel, void *ctx)
{
    LOG_D(TAG, "XcpServerInitializer: %s", channel->id);
    SocketChannel_AddLast(channel, ChannelIdleStateHandler(0, 0, XCP_CONNECTION_TIMEOUT));
    SocketChannel_AddLast(channel, MessageCodec((Device *) ctx));
    SocketChannel_AddLast(channel, XcpServerHandler((Device *)ctx));
}

TINY_LOR
Channel * XcpServer_New(Device *device)
{
    Channel *thiz = NULL;

    do
    {
        thiz = StreamServerChannel_New(XCP_MAX_CONNECTIONS);
        if (thiz == NULL)
        {
            break;
        }

        StreamServerChannel_Initialize(thiz, XcpServerInitializer, device);

        if (RET_FAILED(SocketChannel_Open(thiz, TYPE_TCP_SERVER)))
        {
            LOG_D(TAG, "SocketChannel_Open failed");
            thiz->_onRemove(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(SocketChannel_Bind(thiz, device->port, false)))
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

        if (device->port == 0)
        {
            device->port = thiz->local.socket.port;
        }
    } while (false);

    return thiz;
}

//TINY_LOR
//TinyRet XcpServer_SendQuery(IQ *query, IQ *result, XcpResultHandler handler, void *ctx)
//{
//    SocketChannel_StartWrite(channel, DATA_XCP_MESSAGE, message, 0);
//}
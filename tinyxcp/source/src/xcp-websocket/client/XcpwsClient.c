/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpwsClient.c
 *
 * @remark
 *
 */

#include <tiny_log.h>
#include <channel/SocketChannel.h>
#include <channel/ChannelIdleStateHandler.h>
#include <channel/stream/StreamClientChannel.h>
#include <codec-http/HttpMessageCodec.h>
#include <client/handler/XcpwsClientHandlerContext.h>
#include "handler/XcpwsClientHandler.h"
#include "codec-message/MessageCodec.h"
#include "XcpwsClient.h"

#define TAG     "XcpwsClient"

TINY_LOR
static void XcpwsClientInitializer(Channel *channel, void *ctx)
{
    LOG_D(TAG, "XcpwsClientInitializer: %s", channel->id);
    SocketChannel_AddLast(channel, ChannelIdleStateHandler(0, 0, 30));
    SocketChannel_AddLast(channel, HttpMessageCodec());
    SocketChannel_AddLast(channel, XcpwsClientHandler((Device *)ctx));
}

TINY_LOR
Channel * XcpwsClient_New(Device *device, const char *ip, uint16_t port)
{
    Channel *thiz = NULL;

    do
    {
        thiz = StreamClientChannel_New();
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(StreamClientChannel_Initialize(thiz, XcpwsClientInitializer, device)))
        {
            thiz->_onRemove(thiz);
            break;
        }

        if (RET_FAILED(StreamClientChannel_Connect(thiz, ip, port, 10)))
        {
            thiz->_onRemove(thiz);
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
TinyRet XcpwsClient_SendQuery(Channel *thiz, XcpMessage *query, XcpMessageHandler handler, void *ctx)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        ChannelHandler *h = SocketChannel_GetHandler(thiz, XcpwsClientHandler_Name);
        if (h == NULL)
        {
            ret = TINY_RET_E_INTERNAL;
            break;
        }

        ret = XcpwsClientHandlerContext_SendQuery(h->context, query, handler, ctx);
    } while (false);

    return ret;
}
/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpClient.c
 *
 * @remark
 *
 */

#include <tiny_log.h>
#include <channel/SocketChannel.h>
#include <channel/ChannelIdleStateHandler.h>
#include <channel/stream/StreamClientChannel.h>
#include <codec-message/CustomDataType.h>
#include <codec-message/MessageCodec.h>
#include <client/handler/XcpClientHandler.h>
#include <client/handler/XcpClientHandlerContext.h>
#include "XcpClient.h"

#define TAG     "XcpClient"

TINY_LOR
static void XcpClientInitializer(Channel *channel, void *ctx)
{
    LOG_D(TAG, "XcpClientInitializer: %s", channel->id);
    SocketChannel_AddLast(channel, ChannelIdleStateHandler(0, 0, 30));
    SocketChannel_AddLast(channel, MessageCodec((Device *) ctx));
    SocketChannel_AddLast(channel, XcpClientHandler((Device *)ctx));
}

TINY_LOR
Channel * XcpClient_New(Device *device, const char *ip, uint16_t port)
{
    Channel *thiz = NULL;

    do
    {
        thiz = StreamClientChannel_New();
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(StreamClientChannel_Initialize(thiz, XcpClientInitializer, device)))
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
TinyRet XcpClient_SendQuery(Channel *thiz, XcpMessage *query, XcpMessageHandler handler, void *ctx)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        ChannelHandler *h = SocketChannel_GetHandler(thiz, XcpClientHandler_Name);
        if (h == NULL)
        {
            ret = TINY_RET_E_INTERNAL;
            break;
        }

        XcpClientHandlerContext *context = (XcpClientHandlerContext *) (h->context);
        if (context == NULL)
        {
            ret = TINY_RET_E_INTERNAL;
            break;
        }

        ret = XcpClientHandlerContext_SendQuery(context, query, handler, ctx);
    }  while (false);

    return ret;
}
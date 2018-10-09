/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcmdClient.c
 *
 * @remark
 *
 */

#include <tiny_log.h>
#include <channel/SocketChannel.h>
#include <channel/ChannelIdleStateHandler.h>
#include <channel/stream/StreamClientChannel.h>
#include <codec-http/HttpMessageCodec.h>
#include "handler/XcmdClientHandler.h"
#include "codec-message/MessageCodec.h"
#include "XcmdClient.h"

#define TAG     "XcmdClient"

TINY_LOR
static void XcmdClientInitializer(Channel *channel, void *ctx)
{
    LOG_D(TAG, "XcmdClientInitializer: %s", channel->id);
    SocketChannel_AddLast(channel, ChannelIdleStateHandler(0, 0, 30));
    SocketChannel_AddLast(channel, HttpMessageCodec());
    SocketChannel_AddLast(channel, XcmdClientHandler((Device *)ctx));
}

TINY_LOR
Channel * XcmdClient_New(Device *device, const char *ip, uint16_t port)
{
    Channel *thiz = NULL;

    do
    {
        thiz = StreamClientChannel_New();
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(StreamClientChannel_Initialize(thiz, XcmdClientInitializer, device)))
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
/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   WebcmdServer.c
 *
 * @remark
 *
 */

#include <channel/SocketChannel.h>
#include <channel/ChannelIdleStateHandler.h>
#include <channel/stream/StreamServerChannel.h>
#include <channel/stream/StreamServerChannelContext.h>
#include <codec-http/HttpMessageCodec.h>
#include <tiny_log.h>
#include "WebcmdServer.h"
#include "handler/WebcmdServerHandler.h"

#define TAG     "WebcmdServer"

TINY_LOR
static void WebcmdServerInitializer(Channel *channel, void *ctx)
{
    LOG_D(TAG, "WebcmdServerInitializer: %s", channel->id);
    SocketChannel_AddLast(channel, ChannelIdleStateHandler(0, 0, XCMD_CONNECTION_TIMEOUT));
    SocketChannel_AddLast(channel, HttpMessageCodec());
    SocketChannel_AddLast(channel, WebcmdServerHandler((IotRuntime *)ctx));
}

TINY_LOR
Channel * WebcmdServer_New(IotRuntime *runtime)
{
    Channel *thiz = NULL;

    do
    {
        thiz = StreamServerChannel_New(XCMD_MAX_CONNECTIONS);
        if (thiz == NULL)
        {
            break;
        }

        StreamServerChannel_Initialize(thiz, WebcmdServerInitializer, runtime);

        if (RET_FAILED(SocketChannel_Open(thiz, TYPE_TCP_SERVER)))
        {
            LOG_D(TAG, "SocketChannel_Open failed");
            thiz->_onRemove(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(SocketChannel_Bind(thiz, 0, false)))
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

//        if (device->port == 0)
//        {
//            device->port = thiz->local.socket.port;
//        }
    } while (false);

    return thiz;
}
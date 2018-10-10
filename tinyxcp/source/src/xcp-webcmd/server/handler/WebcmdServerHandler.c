/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   WebcmdServerHandler.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include <tiny_snprintf.h>
#include <tiny_str_equal.h>
#include <channel/SocketChannel.h>
#include <codec-http/HttpMessage.h>
#include "WebcmdServerHandler.h"
#include "HandleGetAccessKey.h"
#include "HandleResetAccessKey.h"
#include "HandlePropertyChanged.h"
#include "HandleEventOccurred.h"
#include "HandleCommon.h"

#define TAG     "WebcmdServerHandler"

TINY_LOR
static bool _ChannelRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len)
{
    IotRuntime *runtime = (IotRuntime *) (thiz->context);
    HttpMessage *message = (HttpMessage *) data;

    LOG_D(TAG, "_HttpRead: %s %s", message->request_line.method, message->request_line.uri);

    do
    {
        if (message->type != HTTP_REQUEST)
        {
            Channel_Close(channel);
            break;
        }

        if (str_equal(message->request_line.uri, "/accesskey", true))
        {
            if (str_equal(message->request_line.method, "GET", false))
            {
                HandleGetAccessKey(channel, runtime);
            }
            else if (str_equal(message->request_line.method, "PUT", false))
            {
                HandleResetAccessKey(channel, runtime);
            }

            break;
        }
        else if (str_equal(message->request_line.uri, "/property", true) && str_equal(message->request_line.method, "PUT", false))
        {
            HandlePropertyChanged(channel, &message->content, runtime);
            break;
        }
        else if (str_equal(message->request_line.uri, "/event", true) && str_equal(message->request_line.method, "PUT", false))
        {
            HandleEventOccurred(channel, &message->content, runtime);
            break;
        }

        sendTextResponse(channel, 404, "NOT FOUND", NULL);
    } while (false);

    return true;
}

TINY_LOR
static void _ChannelEvent(ChannelHandler *thiz, Channel *channel, ChannelTimer *timer)
{
    LOG_D(TAG, "_ChannelEvent: %s", channel->id);
    SocketChannel_Close(channel);
}

TINY_LOR
static void _ChannelActive(ChannelHandler *thiz, Channel *channel)
{
    LOG_D(TAG, "_ChannelActive: %s", channel->id);
}

TINY_LOR
static void _ChannelInactive(ChannelHandler *thiz, Channel *channel)
{
    LOG_D(TAG, "_ChannelInactive: %s", channel->id);
}

TINY_LOR
static void WebcmdServerHandler_Dispose(ChannelHandler *thiz)
{
    RETURN_IF_FAIL(thiz);

    memset(thiz, 0, sizeof(ChannelHandler));
}

TINY_LOR
static void WebcmdServerHandler_Delete(ChannelHandler *thiz)
{
    WebcmdServerHandler_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
static TinyRet WebcmdServerHandler_Construct(ChannelHandler *thiz, IotRuntime *runtime)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        memset(thiz, 0, sizeof(ChannelHandler));

        strncpy(thiz->name, WebcmdServerHandler_Name, CHANNEL_HANDLER_NAME_LEN);

        thiz->invalid = false;
        thiz->onRemove = WebcmdServerHandler_Delete;
        thiz->inType = DATA_HTTP_MESSAGE;
        thiz->outType = DATA_HTTP_MESSAGE;
        thiz->channelActive = _ChannelActive;
        thiz->channelInactive = _ChannelInactive;
        thiz->channelRead = _ChannelRead;
        thiz->channelWrite = NULL;
        thiz->channelEvent = _ChannelEvent;
        thiz->context = runtime;
    } while (0);

    return ret;
}

TINY_LOR
ChannelHandler * WebcmdServerHandler(IotRuntime *runtime)
{
    ChannelHandler *thiz = NULL;

    do
    {
        thiz = (ChannelHandler *)tiny_malloc(sizeof(ChannelHandler));
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(WebcmdServerHandler_Construct(thiz, runtime)))
        {
            WebcmdServerHandler_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}

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
#include <operation/PropertyOperation.h>
#include <channel/SocketChannel.h>
#include <XcpMessage.h>
#include <iq/basic/PingFactory.h>
#include <iq/basic/PongFactory.h>
#include <codec-message/CustomDataType.h>
#include <codec-message/MessageCodec.h>
#include <codec-message/MessageCodecSide.h>
#include <iq/basic/GetPropertiesCodec.h>
#include <iq/IQErrorFactory.h>
#include <iq/basic/SetPropertiesFactory.h>
#include <iq/basic/GetPropertiesFactory.h>
#include <iq/basic/InvokeActionFactory.h>
#include <codec-http/HttpMessage.h>
#include <codec-http/HttpMessageCodec.h>
#include <codec-websocket/WebSocketFrameCodec.h>
#include <tiny_str_equal.h>
#include <sha/sha1.h>
#include <base64/base64.h>
#include <XcpwsClientRuntime.h>
#include <iq/basic/GetAccessKeyFactory.h>
#include <iq/basic/SetAccessKeyFactory.h>
#include "WebcmdServerHandler.h"

#define TAG     "WebcmdServerHandler"

static void sendNotFound(Channel *channel)
{
    HttpMessage *response = HttpMessage_New();
    if (response != NULL)
    {
        HttpMessage_SetResponse(response, 404, "NOT FOUND");
        HttpMessage_SetProtocolIdentifier(response, "HTTP");
        HttpMessage_SetVersion(response, 1, 1);
        HttpHeader_SetInteger(&response->header, "Content-Length", 0);
        SocketChannel_StartWrite(channel, DATA_HTTP_MESSAGE, response, 0);
        HttpMessage_Delete(response);
    }
}

static void sendJsonObject(Channel *channel, int code, const char *reason, JsonObject *object)
{
    do
    {
        if (RET_FAILED(JsonObject_Encode(object, true)))
        {
            break;
        }

        HttpMessage *response = HttpMessage_New();
        if (response == NULL)
        {
            break;
        }

        HttpMessage_SetResponse(response, code, reason);
        HttpMessage_SetProtocolIdentifier(response, "HTTP");
        HttpMessage_SetVersion(response, 1, 1);
        HttpMessage_SetContent(response, "application/json; charset=utf-8", object->size, (const uint8_t *)object->string);

        SocketChannel_StartWrite(channel, DATA_HTTP_MESSAGE, response, 0);
        HttpMessage_Delete(response);
    } while (false);
}

static void sendOK(Channel *channel)
{
    do
    {
        HttpMessage *response = HttpMessage_New();
        if (response == NULL)
        {
            break;
        }

        HttpMessage_SetResponse(response, 200, "OK");
        HttpMessage_SetProtocolIdentifier(response, "HTTP");
        HttpMessage_SetVersion(response, 1, 1);
        HttpHeader_SetInteger(&response->header, "Content-Length", 0);

        SocketChannel_StartWrite(channel, DATA_HTTP_MESSAGE, response, 0);
        HttpMessage_Delete(response);
    } while (false);
}

static void sendError(Channel *channel, IQError *error)
{
    do
    {
        JsonObject *o = JsonObject_New();
        if (o == NULL)
        {
            break;
        }

        JsonObject_PutInteger(o, "status", error->status);
        JsonObject_PutString(o, "description", error->description);

        sendJsonObject(channel, 400, "ERROR", o);

        JsonObject_Delete(o);
    } while (false);
}

static void onGetAccessKeyResult (XcpMessage *result, void *ctx)
{
    Channel *channel = (Channel *)ctx;

    if (result->iq.type == IQ_TYPE_ERROR)
    {
        sendError(channel, &result->iq.content.error);
        return;
    }

    JsonObject *o = JsonObject_New();
    if (o != NULL)
    {
        JsonObject_PutString(o, "key", result->iq.content.result.content.getAccessKey.key);
        sendJsonObject(channel, 200, "OK", o);
        JsonObject_Delete(o);
    }
}

static void onResetAccessKeyResult (XcpMessage *result, void *ctx)
{
    Channel *channel = (Channel *)ctx;

    do
    {
        if (result->iq.type == IQ_TYPE_ERROR)
        {
            sendError(channel, &result->iq.content.error);
            break;
        }

        sendOK(channel);
    } while (false);
}

static void onGetAccessKey(Channel *channel, IotRuntime *runtime)
{
    do
    {
        XcpMessage *query = QueryGetAccessKey_New("");
        if (query == NULL)
        {
            LOG_D(TAG, "QueryGetAccessKey_New FAILED!");
            break;
        }

        if (RET_FAILED(XcpwsClientRuntime_SendQuery(runtime, query, onGetAccessKeyResult, channel)))
        {
            LOG_D(TAG, "XcpwsClientRuntime_SendQuery FAILED");
        }

        XcpMessage_Delete(query);
    } while (false);
}

static void onResetAccessKey(Channel *channel, IotRuntime *runtime)
{
    do
    {
        XcpMessage *query = QuerySetAccessKey_New("", "helloworldhelloworld");
        if (query == NULL)
        {
            LOG_D(TAG, "QuerySetAccessKey_New FAILED!");
            break;
        }

        if (RET_FAILED(XcpwsClientRuntime_SendQuery(runtime, query, onResetAccessKeyResult, channel)))
        {
            LOG_D(TAG, "XcpwsClientRuntime_SendQuery FAILED");
        }

        XcpMessage_Delete(query);
    } while (false);
}

TINY_LOR
static bool _ChannelRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len)
{
    IotRuntime *runtime = (IotRuntime *) (thiz->context);
    HttpMessage *message = (HttpMessage *)data;

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
                onGetAccessKey(channel, runtime);
            }
            else if (str_equal(message->request_line.method, "PUT", false))
            {
                onResetAccessKey(channel, runtime);
            }

            break;
        }
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

/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpwsServerHandler.c
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
#include "XcpwsServerHandler.h"
#include "XcpwsServerHandlerContext.h"

#define TAG     "XcpwsServerHandler"

static void onGet(ChannelHandler *thiz, Channel *channel, const char *id, PropertyOperations *operations)
{
    XcpwsServerHandlerContext *context = (XcpwsServerHandlerContext *) (thiz->context);
    XcpMessage *result = NULL;

    Device_TryReadProperties(context->data->device, operations);

    result = ResultGetProperties_New(id, operations);
    if (result != NULL)
    {
        SocketChannel_StartWrite(channel, DATA_XCP_MESSAGE, result, 0);
    }
    else
    {
        LOG_E(TAG, "ResultGetProperties_New FAILED");
    }
}

static void onSet(ChannelHandler *thiz, Channel *channel, const char *id, PropertyOperations *operations)
{
    XcpwsServerHandlerContext *context = (XcpwsServerHandlerContext *) (thiz->context);
    XcpMessage *result = NULL;

    Device_TryWriteProperties(context->data->device, operations);

    result = ResultSetProperties_New(id, operations);
    if (result != NULL)
    {
        SocketChannel_StartWrite(channel, DATA_XCP_MESSAGE, result, 0);
    }
    else
    {
        LOG_E(TAG, "ResultSetProperties_New FAILED");
    }
}

static void onAction(ChannelHandler *thiz, Channel *channel, const char *id, ActionOperation *operation)
{
    XcpwsServerHandlerContext *context = (XcpwsServerHandlerContext *) (thiz->context);
    XcpMessage *result = NULL;

    LOG_D(TAG, "onAction: %s.%d.%d", operation->aid.did, operation->aid.siid, operation->aid.iid);

    Device_TryInvokeAction(context->data->device, operation);

    result = ResultInvokeAction_New(id, operation);
    if (result != NULL)
    {
        SocketChannel_StartWrite(channel, DATA_XCP_MESSAGE, result, 0);
    }
    else
    {
        LOG_E(TAG, "ResultInvokeAction_New FAILED");
    }
}

static void _sendError(ChannelHandler *thiz, Channel *channel, const char *id, int32_t status, const char *description)
{
    XcpwsServerHandlerContext *context = (XcpwsServerHandlerContext *) (thiz->context);

    XcpMessage * message = IQError_New(XcpwsServerHandlerContext_NextId(context), status, description);
    if (message == NULL)
    {
        LOG_D(TAG, "IQError_New FAILED!");
        return;
    }

    SocketChannel_StartWrite(channel, DATA_XCP_MESSAGE, message, 0);
}

static void onPing(ChannelHandler *thiz, Channel *channel, const char *id)
{
    LOG_D(TAG, "onPing");

    XcpMessage * pong = Pong_New(id);
    if (pong == NULL)
    {
        LOG_D(TAG, "IQError_New FAILED!");
        return;
    }

    SocketChannel_StartWrite(channel, DATA_XCP_MESSAGE, pong, 0);
}

static void onQuery(ChannelHandler *thiz, Channel *channel, const char *id, IQQuery *query)
{
    LOG_D(TAG, "onQuery: %s", id);

    switch (query->method)
    {
        case IQ_METHOD_PING:
            onPing(thiz, channel, id);
            break;

        case IQ_METHOD_GET_PROPERTIES:
            onGet(thiz, channel, id, &query->content.getProperties.properties);
            break;

        case IQ_METHOD_SET_PROPERTIES:
            onSet(thiz, channel, id, &query->content.setProperties.properties);
            break;

        case IQ_METHOD_INVOKE_ACTION:
            onAction(thiz, channel, id, &query->content.invokeAction.operation);
            break;

        default:
            _sendError(thiz, channel, id, -1, "not support method");
            break;
    }
}

static void _handlePong(XcpMessage *message, void *ctx)
{
    // nothing to do!
    LOG_D(TAG, "pong");
}

TINY_LOR
static bool _MessageRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len)
{
    XcpwsServerHandlerContext *context = (XcpwsServerHandlerContext *) (thiz->context);
    XcpMessage *message = (XcpMessage *)data;

    LOG_D(TAG, "_ChannelRead");

    switch (message->iq.type)
    {
        case IQ_TYPE_QUERY:
            onQuery(thiz, channel, message->iq.id, &message->iq.content.query);
            break;

        case IQ_TYPE_RESULT:
        case IQ_TYPE_ERROR:
            XcpwsServerHandlerContext_Handle(context, message);
            break;

        default:
            LOG_E(TAG, "INVALID XcpMessage!");
            break;
    }

    return true;
}

/**
 * GET /webfin/websocket/ HTTP/1.1
 * Host: localhost
 * Upgrade: websocket
 * Connection: Upgrade
 * Sec-WebSocket-Key: xqBt3ImNzJbYqRINxEFlkg==
 * Sec-WebSocket-Version: 13
 * Origin: http://xxxx
 *
 * HTTP/1.1 101 Switching Protocols
 * upgrade: websocket
 * connection: upgrade
 * sec-websocket-accept: K7DJLdLooIwIG/MOpvWFB3y3FE8=
 */
TINY_LOR
static uint32_t getSecWebSocketAccept(const char *key, char accept[256])
{
    char value[256];
    uint8_t digest[SHA1_DIGEST_SIZE];
    sha1_ctx ctx;

    memset(value, 0, 256);
    memset(digest, 0, SHA1_DIGEST_SIZE);

    tiny_snprintf(value, 255, "%s%s", key, "258EAFA5-E914-47DA-95CA-C5AB0DC85B11");

    sha1_init(&ctx);
    sha1_update(&ctx, value, strlen(value));
    sha1_final(digest, &ctx);

    return (uint32_t) base64_encode(digest, SHA1_DIGEST_SIZE, accept);
}

//static void test(void)
//{
//    const char *key = "xqBt3ImNzJbYqRINxEFlkg==";
//    const char *expectAccept= "K7DJLdLooIwIG/MOpvWFB3y3FE8=";
//    char accept[256];
//
//    memset(accept, 0, 256);
//    if (getSecWebSocketAccept(key, accept) == 0)
//    {
//        LOG_D(TAG, "getSecWebSocketAccept = 0");
//    }
//
//    LOG_E(TAG, "         key: %s", key);
//    LOG_E(TAG, "      accept: %s", accept);
//    LOG_E(TAG, "expectAccept: %s", expectAccept);
//}

TINY_LOR
static bool _HandleWebsocketHandshake(ChannelHandler *thiz, Channel *channel, XcpwsServerHandlerContext *context, HttpMessage *request)
{
    bool ret = true;

    do
    {
        HttpMessage *response = NULL;
        const char *upgrade = NULL;
        const char *connection = NULL;
        const char *version = NULL;
        const char *key = NULL;
        char accept[256];

        if (! STR_EQUAL(request->request_line.method, "GET"))
        {
            ret = false;
            break;
        }

        if (! STR_EQUAL(request->request_line.uri, "/controller"))
        {
            ret = false;
            break;
        }

        upgrade = HttpHeader_GetValue(&request->header, "Upgrade");
        if (upgrade == NULL)
        {
            LOG_D(TAG, "Upgrade = null");
            ret = false;
            break;
        }

        if (! str_equal(upgrade, "websocket", true))
        {
            LOG_D(TAG, "Upgrade = %s", upgrade);
            ret = false;
            break;
        }

        connection = HttpHeader_GetValue(&request->header, "Connection");
        if (connection == NULL)
        {
            LOG_D(TAG, "Connection = null");
            ret = false;
            break;
        }

        if (! str_equal(connection, "Upgrade", true))
        {
            LOG_D(TAG, "Connection = %s", connection);
            ret = false;
            break;
        }

        version = HttpHeader_GetValue(&request->header, "Sec-WebSocket-Version");
        if (version == NULL)
        {
            LOG_D(TAG, "Sec-WebSocket-Version = null");
            ret = false;
            break;
        }

        if (! str_equal(version, "13", true))
        {
            LOG_D(TAG, "Sec-WebSocket-Version = %s", version);
            ret = false;
            break;
        }

        key = HttpHeader_GetValue(&request->header, "Sec-WebSocket-Key");
        if (key == NULL)
        {
            LOG_D(TAG, "Sec-WebSocket-Key = null");
            ret = false;
            break;
        }

        memset(accept, 0, 256);
        if (getSecWebSocketAccept(key, accept) == 0)
        {
            LOG_D(TAG, "getSecWebSocketAccept = 0");
            ret = false;
            break;
        }

        response = HttpMessage_New();
        if (response == NULL)
        {
            LOG_E(TAG, "HttpMessage_New FAILED");
            ret = false;
            break;
        }

        HttpMessage_SetResponse(response, 101, "Switching Protocols");
        HttpMessage_SetProtocolIdentifier(response, "HTTP");
        HttpMessage_SetVersion(response, 1, 1);
        HttpHeader_Set(&response->header, "upgrade", "websocket");
        HttpHeader_Set(&response->header, "connection", "upgrade");
        HttpHeader_Set(&response->header, "sec-websocket-accept", accept);
        SocketChannel_StartWrite(channel, DATA_HTTP_MESSAGE, response, 0);
        HttpMessage_Delete(response);

        thiz->channelRead = _MessageRead;
        thiz->inType = DATA_XCP_MESSAGE;
        thiz->outType = DATA_XCP_MESSAGE;
        SocketChannel_RemoveHandler(channel, HttpMessageCodec_Name);
        SocketChannel_AddBefore(channel, XcpwsServerHandler_Name, WebSocketFrameCodec());
        SocketChannel_AddBefore(channel, XcpwsServerHandler_Name, MessageCodec(context->data->device, MESSAGE_CODEC_SERVER));
    } while (false);

    return ret;
}

TINY_LOR
static bool _HandleHttpRequest(Channel *channel, XcpwsServerHandlerContext *context, HttpMessage *request)
{
    bool ret = false;

    do
    {
        HttpRequestHandlerContext *c = NULL;

        if (context->data->handlers == NULL)
        {
            break;
        }

        c = HttpRequestHandlers_Get(context->data->handlers, request->request_line.method, request->request_line.uri);
        if (c == NULL)
        {
            break;
        }

        HttpMessage *response = c->handler(request, c->ctx);
        if (response == NULL)
        {
            break;
        }

        SocketChannel_StartWrite(channel, DATA_HTTP_MESSAGE, response, 0);
        HttpMessage_Delete(response);
        ret = true;
    } while (false);

    return ret;
}

TINY_LOR
static bool _HttpRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len)
{
    XcpwsServerHandlerContext *context = (XcpwsServerHandlerContext *) (thiz->context);
    HttpMessage *message = (HttpMessage *)data;

    LOG_E(TAG, "----------------------------------------------------");
    LOG_D(TAG, "_HttpRead: %s %s", message->request_line.method, message->request_line.uri);

    do
    {
        if (message->type != HTTP_REQUEST)
        {
            Channel_Close(channel);
            break;
        }

        if (_HandleWebsocketHandshake(thiz, channel, context, message))
        {
            break;
        }

        if (! _HandleHttpRequest(channel, context, message))
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

            // Channel_Close(channel);
            break;
        }

    } while (false);

    return true;
}

TINY_LOR
static void _Ping(ChannelHandler *thiz, Channel *channel)
{
    XcpwsServerHandlerContext *context = (XcpwsServerHandlerContext *) (thiz->context);

    LOG_D(TAG, "ping");

    do
    {
        XcpMessage * message = Ping_New(XcpwsServerHandlerContext_NextId(context));
        if (message == NULL)
        {
            LOG_D(TAG, "XcpMessage_New FAILED!");
            break;
        }

        if (RET_FAILED(XcpwsServerHandlerContext_AddHandler(thiz->context, message->iq.id, _handlePong, thiz)))
        {
            LOG_D(TAG, "XcpwsServerHandlerContext_AddHandler FAILED!");
            return;
        }

        SocketChannel_StartWrite(channel, DATA_XCP_MESSAGE, message, 0);
    } while (false);
}

TINY_LOR
static void _ChannelEvent(ChannelHandler *thiz, Channel *channel, ChannelTimer *timer)
{
    XcpwsServerHandlerContext *context = (XcpwsServerHandlerContext *) (thiz->context);

    LOG_D(TAG, "_ChannelEvent: %s", channel->id);

     SocketChannel_Close(channel);

#if 0
    if (context->handlers.list.size > 30)
    {
        SocketChannel_Close(channel);
    }
    else
    {
        // _Ping(thiz, channel);
    }
#endif
}

TINY_LOR
static void _ChannelActive(ChannelHandler *thiz, Channel *channel)
{
    LOG_D(TAG, "_ChannelActive: %s", channel->id);

    XcpwsServerHandlerContext *context = (XcpwsServerHandlerContext *) (thiz->context);
    thiz->channelEvent = _ChannelEvent;
    context->channel = channel;
}

TINY_LOR
static void _ChannelInactive(ChannelHandler *thiz, Channel *channel)
{
    LOG_D(TAG, "_ChannelInactive: %s", channel->id);
}

TINY_LOR
static void XcpwsServerHandler_Dispose(ChannelHandler *thiz)
{
    RETURN_IF_FAIL(thiz);

    XcpwsServerHandlerContext_Delete((XcpwsServerHandlerContext *) (thiz->context));
    memset(thiz, 0, sizeof(ChannelHandler));
}

TINY_LOR
static void XcpwsServerHandler_Delete(ChannelHandler *thiz)
{
    XcpwsServerHandler_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
static TinyRet XcpwsServerHandler_Construct(ChannelHandler *thiz, XcpwsServerContext *data)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        memset(thiz, 0, sizeof(ChannelHandler));

        strncpy(thiz->name, XcpwsServerHandler_Name, CHANNEL_HANDLER_NAME_LEN);

        thiz->invalid = false;
        thiz->onRemove = XcpwsServerHandler_Delete;
        thiz->inType = DATA_HTTP_MESSAGE;
        thiz->outType = DATA_HTTP_MESSAGE;
        thiz->channelActive = _ChannelActive;
        thiz->channelInactive = _ChannelInactive;
        thiz->channelRead = _HttpRead;
        thiz->channelWrite = NULL;
        thiz->channelEvent = _ChannelEvent;

        thiz->context = XcpwsServerHandlerContext_New(data);
        if (thiz->context == NULL)
        {
            LOG_E(TAG, "XcpwsServerHandlerContext_New FAILED");
            ret = TINY_RET_E_NEW;
            break;
        }
    } while (0);

    return ret;
}

TINY_LOR
ChannelHandler * XcpwsServerHandler(XcpwsServerContext *data)
{
    ChannelHandler *thiz = NULL;

    do
    {
        thiz = (ChannelHandler *)tiny_malloc(sizeof(ChannelHandler));
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(XcpwsServerHandler_Construct(thiz, data)))
        {
            XcpwsServerHandler_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}

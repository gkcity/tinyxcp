/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcmdClientHandler.h
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
#include <codec-http/HttpMessage.h>
#include <codec-http/HttpMessageCodec.h>
#include <codec-websocket/WebSocketFrame.h>
#include <codec-websocket/WebSocketFrameFactory.h>
#include <codec-websocket/WebSocketFrameCodec.h>
#include <codec-websocket/WebSocketFrameEncoder.h>
#include <iq/basic/PingFactory.h>
#include <iq/basic/GetPropertiesCodec.h>
#include <iq/basic/GetPropertiesFactory.h>
#include <iq/basic/SetPropertiesFactory.h>
#include <iq/basic/InvokeActionFactory.h>
#include <iq/IQErrorFactory.h>
#include <client/verifier/XcpClientVerifier.h>
#include <XcpKeyCreator.h>
#include <codec-message/MessageCodecSide.h>
#include "codec-message/CustomDataType.h"
#include "codec-message/MessageCodec.h"
#include "codec-binary/WebSocketBinaryFrameCodec.h"
#include "XcmdClientHandler.h"
#include "XcmdClientHandlerContext.h"

#define TAG     "XcmdClientHandler"

static void onGet(ChannelHandler *thiz, Channel *channel, const char *id, PropertyOperations *operations)
{
//    XcmdClientHandlerContext *context = (XcmdClientHandlerContext *) (thiz->context);
//    XcpMessage *result = NULL;
//
//    Device_TryReadProperties(context->device, operations);
//
//    result = ResultGetProperties_New(id, operations);
//    if (result != NULL)
//    {
//        SocketChannel_StartWrite(channel, DATA_XCP_MESSAGE, result, 0);
//    }
//    else
//    {
//        LOG_E(TAG, "ResultGetProperties_New FAILED");
//    }
}

static void onSet(ChannelHandler *thiz, Channel *channel, const char *id, PropertyOperations *operations)
{
//    XcmdClientHandlerContext *context = (XcmdClientHandlerContext *) (thiz->context);
//    XcpMessage *result = NULL;
//
//    Device_TryWriteProperties(context->device, operations);
//
//    result = ResultSetProperties_New(id, operations);
//    if (result != NULL)
//    {
//        SocketChannel_StartWrite(channel, DATA_XCP_MESSAGE, result, 0);
//    }
//    else
//    {
//        LOG_E(TAG, "ResultSetProperties_New FAILED");
//    }
}

static void onAction(ChannelHandler *thiz, Channel *channel, const char *id, ActionOperation *operation)
{
//    XcmdClientHandlerContext *context = (XcmdClientHandlerContext *) (thiz->context);
//    XcpMessage *result = NULL;
//
//    LOG_D(TAG, "onAction: %s.%d.%d", operation->aid.did, operation->aid.siid, operation->aid.iid);
//
//    Device_TryInvokeAction(context->device, operation);
//
//    result = ResultInvokeAction_New(id, operation);
//    if (result != NULL)
//    {
//        SocketChannel_StartWrite(channel, DATA_XCP_MESSAGE, result, 0);
//    }
//    else
//    {
//        LOG_E(TAG, "ResultInvokeAction_New FAILED");
//    }
}

static void _sendError(ChannelHandler *thiz, Channel *channel, const char *id, int32_t status, const char *description)
{
    XcmdClientHandlerContext *context = (XcmdClientHandlerContext *) (thiz->context);

    XcpMessage * message = IQError_New(XcmdClientHandlerContext_NextId(context), status, description);
    if (message == NULL)
    {
        LOG_D(TAG, "IQError_New FAILED!");
        return;
    }

    SocketChannel_StartWrite(channel, DATA_XCP_MESSAGE, message, 0);
}

static void onQuery(ChannelHandler *thiz, Channel *channel, const char *id, IQQuery *query)
{
    LOG_D(TAG, "onQuery: %s", id);

    switch (query->method)
    {
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

static void onVerifySuccess (HKDF *deviceToServerKey, HKDF *serverToDeviceKey, void *ctx)
{
    XcmdClientHandlerContext *context = (XcmdClientHandlerContext *) (ctx);

    LOG_D(TAG, "onVerifySuccess");

    SocketChannel_AddBefore(context->channel, MessageCodec_Name, WebSocketBinaryFrameCodec(serverToDeviceKey, deviceToServerKey));
}

static void onVerifyFailure (void *ctx)
{
    XcmdClientHandlerContext *context = (XcmdClientHandlerContext *) (ctx);

    LOG_D(TAG, "onVerifyFailure");
}

TINY_LOR
static bool _MessageRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len)
{
    XcmdClientHandlerContext *context = (XcmdClientHandlerContext *) (thiz->context);
    XcpMessage *message = (XcpMessage *)data;

    LOG_D(TAG, "_ChannelRead");

    switch (message->iq.type)
    {
        case IQ_TYPE_QUERY:
            onQuery(thiz, channel, message->iq.id, &message->iq.content.query);
            break;

        case IQ_TYPE_RESULT:
        case IQ_TYPE_ERROR:
            XcmdClientHandlerContext_Handle(context, message);
            break;

        default:
            LOG_E(TAG, "INVALID XcpMessage!");
            break;
    }

    return true;
}

TINY_LOR
static bool _HttpRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len)
{
    XcmdClientHandlerContext *context = (XcmdClientHandlerContext *) (thiz->context);
    HttpMessage *message = (HttpMessage *)data;

    LOG_D(TAG, "_HttpRead");

    if (message->status_line.code == 101)
    {
        LOG_D(TAG, "WebSocket handshake succeed: %d %s", message->status_line.code, message->status_line.status);
        thiz->channelRead = _MessageRead;
        thiz->inType = DATA_XCP_MESSAGE;
        thiz->outType = DATA_XCP_MESSAGE;
        SocketChannel_RemoveHandler(channel, HttpMessageCodec_Name);
        SocketChannel_AddBefore(channel, XcmdClientHandler_Name, WebSocketFrameCodec());
//        SocketChannel_AddBefore(channel, XcmdClientHandler_Name, MessageCodec(context->device, MESSAGE_CODEC_CLIENT));
//        XcpClientVerifier_Start(context->verifier, onVerifySuccess, onVerifyFailure, thiz->context);
    }
    else
    {
        LOG_D(TAG, "WebSocket handshake failed: %d", message->status_line.code);
    }

    return true;
}

TINY_LOR
static void _Output (const uint8_t *data, uint64_t size, void *ctx)
{
    Channel *channel = (Channel *)ctx;
    SocketChannel_StartWrite(channel, DATA_RAW, data, (uint32_t)size);
}

#if 0
TINY_LOR
static void _Ping(ChannelHandler *thiz, Channel *channel)
{
    XcmdClientHandlerContext *context = (XcmdClientHandlerContext *) (thiz->context);
    WebSocketFrame * frame = NULL;

    LOG_D(TAG, "ping");

    do
    {
        frame = WebSocketFrameFactory_NewPingFrame();
        if (frame == NULL)
        {
            LOG_E(TAG, "WebSocketFrameFactory_NewPingFrame FAILED");
            break;
        }

        WebSocketFrameEncoder_Encode(frame, _Output, channel);
    } while (false);

    if (frame != NULL)
    {
        WebSocketFrame_Delete(frame);
    }
}

#else

TINY_LOR
static void _handlePong(XcpMessage *message, void *ctx)
{
    // nothing to do!
    LOG_D(TAG, "pong");
}

TINY_LOR
static void _Ping(ChannelHandler *thiz, Channel *channel)
{
    XcmdClientHandlerContext *context = (XcmdClientHandlerContext *) (thiz->context);

    LOG_D(TAG, "ping");

    do
    {
        XcpMessage * message = Ping_New(XcmdClientHandlerContext_NextId(context));
        if (message == NULL)
        {
            LOG_D(TAG, "XcpMessage_New FAILED!");
            break;
        }

        if (RET_FAILED(XcmdClientHandlerContext_AddHandler(thiz->context, message->iq.id, _handlePong, thiz)))
        {
            LOG_D(TAG, "XcpClientHandlerContext_AddHandler FAILED!");
            return;
        }

        SocketChannel_StartWrite(channel, DATA_XCP_MESSAGE, message, 0);
    } while (false);
}

#endif

TINY_LOR
static void _ChannelEvent(ChannelHandler *thiz, Channel *channel, ChannelTimer *timer)
{
    XcmdClientHandlerContext *context = (XcmdClientHandlerContext *) (thiz->context);

    LOG_D(TAG, "_ChannelEvent: %s", channel->id);

    if (context->handlers.list.size > 30)
    {
        SocketChannel_Close(channel);
    }
    else
    {
        _Ping(thiz, channel);
    }
}

/**
 * GET /webfin/websocket/ HTTP/1.1
 * Host: localhost
 * Upgrade: websocket
 * Connection: Upgrade
 * Sec-WebSocket-Key: xqBt3ImNzJbYqRINxEFlkg==
 * Sec-WebSocket-Version: 13
 * Origin: http://xxxx
 */
TINY_LOR
static void startHandshake(ChannelHandler *thiz, Channel *channel)
{
    HttpMessage *message = HttpMessage_New();

    LOG_D(TAG, "startHandshake");

    HttpMessage_SetRequest(message, "GET", "/endpoint");
    HttpMessage_SetProtocolIdentifier(message, "HTTP");
    HttpMessage_SetVersion(message, 1, 1);

    HttpHeader_SetHost(&message->header, "localhost", 80);
    HttpHeader_Set(&message->header, "Upgrade", "websocket");
    HttpHeader_Set(&message->header, "Connection", "Upgrade");
    HttpHeader_Set(&message->header, "Sec-WebSocket-Key", "xqBt3ImNzJbYqRINxEFlkg==");
    HttpHeader_Set(&message->header, "Origin", "http://localhost:9090");
    HttpHeader_SetInteger(&message->header, "Sec-WebSocket-Version", 13);

    SocketChannel_StartWrite(channel, DATA_HTTP_MESSAGE, message, 1);

    HttpMessage_Delete(message);
}

/**
 * HTTP/1.1 101 Switching Protocols
 * upgrade: websocket
 * connection: upgrade
 * sec-websocket-accept: K7DJLdLooIwIG/MOpvWFB3y3FE8=
 */

/**
 * HTTP/1.1 101 Switching Protocols
 * Upgrade: websocket
 * Connection: Upgrade
 * Sec-WebSocket-Accept: K7DJLdLooIwIG/MOpvWFB3y3FE8=
 */

TINY_LOR
static void _ChannelActive(ChannelHandler *thiz, Channel *channel)
{
    LOG_D(TAG, "_ChannelActive: %s", channel->id);

    XcmdClientHandlerContext *context = (XcmdClientHandlerContext *) (thiz->context);
    thiz->channelEvent = _ChannelEvent;
    context->channel = channel;

    startHandshake(thiz, channel);
}

TINY_LOR
static void _ChannelInactive(ChannelHandler *thiz, Channel *channel)
{
    LOG_D(TAG, "_ChannelInactive: %s", channel->id);
}

TINY_LOR
static void XcmdClientHandler_Dispose(ChannelHandler *thiz)
{
    RETURN_IF_FAIL(thiz);

    XcmdClientHandlerContext_Delete((XcmdClientHandlerContext *) (thiz->context));
    memset(thiz, 0, sizeof(ChannelHandler));
}

TINY_LOR
static void XcmdClientHandler_Delete(ChannelHandler *thiz)
{
    XcmdClientHandler_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
static TinyRet XcmdClientHandler_Construct(ChannelHandler *thiz)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        memset(thiz, 0, sizeof(ChannelHandler));

        strncpy(thiz->name, XcmdClientHandler_Name, CHANNEL_HANDLER_NAME_LEN);

        thiz->invalid = false;
        thiz->onRemove = XcmdClientHandler_Delete;
        thiz->inType = DATA_HTTP_MESSAGE;
        thiz->outType = DATA_HTTP_MESSAGE;
        thiz->channelActive = _ChannelActive;
        thiz->channelInactive = _ChannelInactive;
        thiz->channelRead = _HttpRead;
        thiz->channelWrite = NULL;
        thiz->channelEvent = _ChannelEvent;

        thiz->context = XcmdClientHandlerContext_New();
        if (thiz->context == NULL)
        {
            LOG_E(TAG, "XcmdClientHandlerContext_New FAILED");
            ret = TINY_RET_E_NEW;
            break;
        }
    } while (0);

    return ret;
}

TINY_LOR
ChannelHandler * XcmdClientHandler(void)
{
    ChannelHandler *thiz = NULL;

    do
    {
        thiz = (ChannelHandler *)tiny_malloc(sizeof(ChannelHandler));
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(XcmdClientHandler_Construct(thiz)))
        {
            XcmdClientHandler_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}
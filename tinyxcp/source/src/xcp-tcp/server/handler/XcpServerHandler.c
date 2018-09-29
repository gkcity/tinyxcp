/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpServerHandler.c
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
#include <codec-message/CustomDataType.h>
#include <codec-message/MessageCodec.h>
#include <codec-binary/XcpBinaryCodec.h>
#include <iq/basic/GetPropertiesCodec.h>
#include <iq/IQErrorFactory.h>
#include <iq/basic/SetPropertiesFactory.h>
#include <iq/basic/GetPropertiesFactory.h>
#include <iq/basic/InvokeActionFactory.h>
#include "XcpServerHandler.h"
#include "XcpServerHandlerContext.h"

#define TAG     "XcpServerHandler"

static void onGet(ChannelHandler *thiz, Channel *channel, const char *id, PropertyOperations *operations)
{
    XcpServerHandlerContext *context = (XcpServerHandlerContext *) (thiz->context);
    XcpMessage *result = NULL;

    Device_TryReadProperties(context->device, operations);

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
    XcpServerHandlerContext *context = (XcpServerHandlerContext *) (thiz->context);
    XcpMessage *result = NULL;

    Device_TryWriteProperties(context->device, operations);

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
    XcpServerHandlerContext *context = (XcpServerHandlerContext *) (thiz->context);
    XcpMessage *result = NULL;

    LOG_D(TAG, "onAction: %s.%d.%d", operation->aid.did, operation->aid.siid, operation->aid.iid);

    Device_TryInvokeAction(context->device, operation);

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
    XcpServerHandlerContext *context = (XcpServerHandlerContext *) (thiz->context);

    XcpMessage * message = IQError_New(XcpServerHandlerContext_NextId(context), status, description);
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

static void _handlePong(XcpMessage *message, void *ctx)
{
    // nothing to do!
    LOG_D(TAG, "pong");
}

TINY_LOR
static bool _ChannelRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len)
{
    XcpServerHandlerContext *context = (XcpServerHandlerContext *) (thiz->context);
    XcpMessage *message = (XcpMessage *)data;

    LOG_D(TAG, "_ChannelRead");

    switch (message->iq.type)
    {
        case IQ_TYPE_QUERY:
            onQuery(thiz, channel, message->iq.id, &message->iq.content.query);
            break;

        case IQ_TYPE_RESULT:
        case IQ_TYPE_ERROR:
            XcpServerHandlerContext_Handle(context, message);
            break;

        default:
            LOG_E(TAG, "INVALID XcpMessage!");
            break;
    }

    return true;
}

TINY_LOR
static void _Ping(ChannelHandler *thiz, Channel *channel)
{
    XcpServerHandlerContext *context = (XcpServerHandlerContext *) (thiz->context);

    LOG_D(TAG, "ping");

    do
    {
        XcpMessage * message = Ping_New(XcpServerHandlerContext_NextId(context));
        if (message == NULL)
        {
            LOG_D(TAG, "XcpMessage_New FAILED!");
            break;
        }

        if (RET_FAILED(XcpServerHandlerContext_AddHandler(thiz->context, message->iq.id, _handlePong, thiz)))
        {
            LOG_D(TAG, "XcpServerHandlerContext_AddHandler FAILED!");
            return;
        }

        SocketChannel_StartWrite(channel, DATA_XCP_MESSAGE, message, 0);
    } while (false);
}

TINY_LOR
static void _ChannelEvent(ChannelHandler *thiz, Channel *channel, ChannelTimer *timer)
{
    XcpServerHandlerContext *context = (XcpServerHandlerContext *) (thiz->context);

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

TINY_LOR
static void _ChannelActive(ChannelHandler *thiz, Channel *channel)
{
    LOG_D(TAG, "_ChannelActive: %s", channel->id);

    XcpServerHandlerContext *context = (XcpServerHandlerContext *) (thiz->context);
    thiz->channelEvent = _ChannelEvent;
    context->channel = channel;
}

TINY_LOR
static void _ChannelInactive(ChannelHandler *thiz, Channel *channel)
{
    LOG_D(TAG, "_ChannelInactive: %s", channel->id);
}

TINY_LOR
static void XcpServerHandler_Dispose(ChannelHandler *thiz)
{
    RETURN_IF_FAIL(thiz);

    XcpServerHandlerContext_Delete((XcpServerHandlerContext *) (thiz->context));
    memset(thiz, 0, sizeof(ChannelHandler));
}

TINY_LOR
static void XcpServerHandler_Delete(ChannelHandler *thiz)
{
    XcpServerHandler_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
static TinyRet XcpServerHandler_Construct(ChannelHandler *thiz, Device *device)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        memset(thiz, 0, sizeof(ChannelHandler));

        strncpy(thiz->name, XcpServerHandler_Name, CHANNEL_HANDLER_NAME_LEN);
        thiz->onRemove = XcpServerHandler_Delete;

        thiz->inType = DATA_XCP_MESSAGE;
        thiz->outType = DATA_XCP_MESSAGE;
        thiz->channelActive = _ChannelActive;
        thiz->channelInactive = _ChannelInactive;
        thiz->channelRead = _ChannelRead;
        thiz->channelWrite = NULL;
        thiz->channelEvent = _ChannelEvent;

        thiz->context = XcpServerHandlerContext_New(device);
        if (thiz->context == NULL)
        {
            LOG_E(TAG, "XcpServerHandlerContext_New FAILED");
            ret = TINY_RET_E_NEW;
            break;
        }
    } while (0);

    return ret;
}

TINY_LOR
ChannelHandler * XcpServerHandler(Device *device)
{
    ChannelHandler *thiz = NULL;

    do
    {
        thiz = (ChannelHandler *)tiny_malloc(sizeof(ChannelHandler));
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(XcpServerHandler_Construct(thiz, device)))
        {
            XcpServerHandler_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}
/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   MessageCodec.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_malloc.h>
#include <channel/SocketChannel.h>
#include <XcpMessage.h>
#include <tiny_log.h>
#include <codec/JsonDecoder.h>
#include <codec-websocket/WebSocketFrame.h>
#include <codec-websocket/WebSocketFrameFactory.h>
#include <XcpMessageCodec.h>
#include "MessageCodec.h"
#include "MessageCodecContext.h"
#include "CustomDataType.h"

#define TAG "MessageCodec"

TINY_LOR
static bool _ChannelRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len)
{
    MessageCodecContext *context = (MessageCodecContext *)thiz->context;
    const WebSocketFrame *frame = (WebSocketFrame *) data;
    JsonObject * object = NULL;
    XcpMessage * message = NULL;

    LOG_D(TAG, "_ChannelRead");

    /**
     *
     * 1. put data to context->buffer
     *
     * 2. Decode buffer to a JsonObject
     *    JsonObject *object = decode(buffer);
     *
     * 3. Decode JsonObject to a XcpMessage
     *    XcpMessage *message = decode(object);
     *
     * 4. Next
     *    if (message != NULL)
     *    {
     *         SocketChannel_NextRead(channel, DATA_XCP_MESSAGE, message, 0);
     *    }
     */

    do
    {
        TinyRet ret = TINY_RET_OK;
        JsonDecoder decoder;

        if (frame->opcode != OPCODE_TEXT_FRAME)
        {
            break;
        }

        ret = ByteBuffer_Put(&context->buffer, frame->data, (uint32_t) frame->length);
        if (RET_FAILED(ret))
        {
            //LOG_E(TAG, "ByteBuffer_Put FAILED: %s", tiny_ret_to_str(ret));
            break;
        }

        LOG_D(TAG, "buffer: %s", (const char *)(context->buffer.bytes));

        ret = JsonDecoder_Construct(&decoder);
        if (RET_FAILED(ret))
        {
            //LOG_E(TAG, "JsonDecoder_Construct FAILED: %s", tiny_ret_to_str(ret));
            break;
        }

        object = JsonDecoder_Parse(&decoder, (const char *)context->buffer.bytes, JSON_DECODE_LOW_MEMORY);
        if (object == NULL)
        {
            JsonDecoder_Dispose(&decoder);
            break;
        }

        ByteBuffer_Clear(&context->buffer);

        message = XcpMessageCodec_Decode(object);
        if (message == NULL)
        {
            LOG_E(TAG, "XcpMessageCodec_Decode FAILED, JsonObject not a XcpMessage");
            JsonDecoder_Dispose(&decoder);
            break;
        }

        SocketChannel_NextRead(channel, DATA_XCP_MESSAGE, message, 1);
    } while (false);

    if (object != NULL)
    {
        JsonObject_Delete(object);
    }

    if (message != NULL)
    {
        XcpMessage_Delete(message);
    }

    return true;
}

TINY_LOR
static bool _ChannelWrite(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len)
{
    MessageCodecContext *context = (MessageCodecContext *)thiz->context;
    XcpMessage *message = (XcpMessage *)data;
    JsonObject *object = NULL;
    WebSocketFrame *frame = NULL;

    LOG_D(TAG, "_ChannelWrite");

    /**
     * 1. Encode
     *
     *    uint8_t *bytes = encode(message);
     *    uint32_t length = encode(message);
     *
     * 2. Next
     *
     *    SocketChannel_NextWrite(channel, DATA_RAW, bytes, length);
     */

    do
    {
        TinyRet ret = TINY_RET_OK;

        object = XcpMessageCodec_Encode(message);
        if (object == NULL)
        {
            LOG_E(TAG, "XcpMessageCodec_Encode FAILED, invalid message");
            break;
        }

        ret = JsonObject_Encode(object, false);
        if (RET_FAILED(ret))
        {
            //LOG_E(TAG, "JsonObject_Encode FAILED, %s", tiny_ret_to_str(ret));
            break;
        }

        LOG_D(TAG, "write: %s", object->string);

        frame = WebSocketFrameFactory_NewTextFrame(true, object->string);
        if (frame == NULL)
        {
            LOG_E(TAG, "WebSocketFrameFactory_NewTextFrame FAILED");
            break;
        }

        if (context->side == MESSAGE_CODEC_CLIENT)
        {
            frame->mask = true;
            frame->maskingKey[0] = 0xCB;
            frame->maskingKey[1] = 0x3E;
            frame->maskingKey[2] = 0x2B;
            frame->maskingKey[3] = 0x74;
        }
        else
        {
            frame->mask = false;
        }

        SocketChannel_NextWrite(channel, DATA_WEBSOCKET_FRAME, frame, 0);
    } while (false);

    if (object != NULL)
    {
        JsonObject_Delete(object);
    }

    if (frame != NULL)
    {
        WebSocketFrame_Delete(frame);
    }

    return true;
}

TINY_LOR
static TinyRet XcpMessageCodec_Dispose(ChannelHandler *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->context != NULL)
    {
        MessageCodecContext_Delete(thiz->context);
        thiz->context = NULL;
    }

    memset(thiz, 0, sizeof(ChannelHandler));

    return TINY_RET_OK;
}

TINY_LOR
static void XcpMessageCodec_Delete(ChannelHandler *thiz)
{
    XcpMessageCodec_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
static TinyRet XcpMessageCodec_Construct(ChannelHandler *thiz, Device *device, MessageCodecSide side)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(device, TINY_RET_E_ARG_NULL);

    memset(thiz, 0, sizeof(ChannelHandler));

    strncpy(thiz->name, MessageCodec_Name, CHANNEL_HANDLER_NAME_LEN);

    thiz->invalid = false;
    thiz->onRemove = XcpMessageCodec_Delete;
    thiz->inType = DATA_WEBSOCKET_FRAME;
    thiz->outType = DATA_XCP_MESSAGE;
    thiz->channelRead = _ChannelRead;
    thiz->channelWrite = _ChannelWrite;
    thiz->context = MessageCodecContext_New(device, side);

    return TINY_RET_OK;
}

TINY_LOR
ChannelHandler * MessageCodec(Device *device, MessageCodecSide side)
{
    ChannelHandler *thiz = NULL;

    do
    {
        thiz = (ChannelHandler *)tiny_malloc(sizeof(ChannelHandler));
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(XcpMessageCodec_Construct(thiz, device, side)))
        {
            XcpMessageCodec_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}

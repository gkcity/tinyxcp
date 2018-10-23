/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   WebSocketBinaryFrameCodec.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "WebSocketBinaryFrameCodec.h"
#include "WebSocketBinaryFrameCodecContext.h"
#include "WebSocketBinaryFrameDecoder.h"
#include "WebSocketBinaryFrameEncoder.h"
#include <tiny_log.h>
#include <tiny_malloc.h>
#include <channel/SocketChannel.h>
#include <codec-websocket/WebSocketFrame.h>
#include <codec-websocket/WebSocketFrameFactory.h>

#define TAG "WebSocketBinaryFrameCodec"

TINY_LOR
static TinyRet WebSocketBinaryFrameCodec_Construct(ChannelHandler *thiz, HKDF *inKey, HKDF *outKey);

TINY_LOR
static TinyRet WebSocketBinaryFrameCodec_Dispose(ChannelHandler *thiz);

TINY_LOR
static void WebSocketBinaryFrameCodec_Delete(ChannelHandler *thiz);

TINY_LOR
static bool _ChannelRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len);

TINY_LOR
static bool _ChannelWrite(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len);

TINY_LOR
static void _ChannelDecode(ChannelHandler *thiz, Channel *channel, WebSocketFrame *frame);

TINY_LOR
static void _ChannelEncode(ChannelHandler *thiz, Channel *channel, const uint8_t *in, uint32_t inBytes);

TINY_LOR
ChannelHandler * WebSocketBinaryFrameCodec(HKDF *inKey, HKDF *outKey)
{
    ChannelHandler *thiz = NULL;

    do
    {
        thiz = (ChannelHandler *)tiny_malloc(sizeof(ChannelHandler));
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(WebSocketBinaryFrameCodec_Construct(thiz, inKey, outKey)))
        {
            WebSocketBinaryFrameCodec_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}

TINY_LOR
static void WebSocketBinaryFrameCodec_Delete(ChannelHandler *thiz)
{
    WebSocketBinaryFrameCodec_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
static TinyRet WebSocketBinaryFrameCodec_Construct(ChannelHandler *thiz, HKDF *inKey, HKDF *outKey)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(inKey, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(outKey, TINY_RET_E_ARG_NULL);

    memset(thiz, 0, sizeof(ChannelHandler));

    strncpy(thiz->name, WebSocketBinaryFrameCodec_Name, CHANNEL_HANDLER_NAME_LEN);
    thiz->onRemove = WebSocketBinaryFrameCodec_Delete;
    thiz->inType = DATA_WEBSOCKET_FRAME;
    thiz->outType = DATA_WEBSOCKET_FRAME;
    thiz->channelRead = _ChannelRead;
    thiz->channelWrite = _ChannelWrite;
    thiz->context = WebSocketBinaryFrameCodecContext_New(inKey, outKey);

    return TINY_RET_OK;
}

TINY_LOR
static TinyRet WebSocketBinaryFrameCodec_Dispose(ChannelHandler *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->context != NULL)
    {
        WebSocketBinaryFrameCodecContext_Delete(thiz->context);
        thiz->context = NULL;
    }

    memset(thiz, 0, sizeof(ChannelHandler));

    return TINY_RET_OK;
}

TINY_LOR
static bool _ChannelRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len)
{
    LOG_D(TAG, "_ChannelRead: %d bytes from %s", len, channel->id);

    RETURN_VAL_IF_FAIL(thiz, false);
    RETURN_VAL_IF_FAIL(channel, false);
    RETURN_VAL_IF_FAIL(data, false);

    if (type == DATA_WEBSOCKET_FRAME)
    {
        _ChannelDecode(thiz, channel, (WebSocketFrame *) data);
    }
    else
    {
        LOG_D(TAG, "_channelRead inType error: %d", type);
    }

    return true;
}

TINY_LOR
static bool _ChannelWrite(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len)
{
    RETURN_VAL_IF_FAIL(thiz, false);
    RETURN_VAL_IF_FAIL(channel, false);
    RETURN_VAL_IF_FAIL(data, false);

    LOG_D(TAG, "_ChannelWrite: %d bytes to %s", len, channel->id);

    if (((WebSocketBinaryFrameCodecContext *) thiz->context)->started)
    {
        _ChannelEncode(thiz, channel, data, len);
    }
    else
    {
        SocketChannel_NextWrite(channel, type, data, len);
    }

    return true;
}

/**
 * input = frame | frame | frame | ...
 * frame = [header][encrypted data][signature]
 * length = the length of encrypted data, 2 bytes, no larger than 1024 bytes
 * signature = 16 bytes
 */
TINY_LOR
static void _ChannelDecode(ChannelHandler *thiz, Channel *channel, WebSocketFrame *frame)
{
    WebSocketBinaryFrameCodecContext *ctx = (WebSocketBinaryFrameCodecContext *) thiz->context;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(channel);
    RETURN_IF_FAIL(frame);

    LOG_D(TAG, "_ChannelDecode: %d bytes", (uint32_t)frame->length);

    do
    {
        ctx->started = true;

        if (RET_FAILED(WebSocketBinaryFrameDecoder_Decode(frame, ctx->inboundBinaryMessageCount, &ctx->inKey)))
        {
            LOG_D(TAG, "WebSocketBinaryFrameDecoder_Decode FAILED");
            break;
        }

        SocketChannel_NextRead(channel, DATA_WEBSOCKET_FRAME, frame, 0);

        ctx->inboundBinaryMessageCount++;
    } while (false);
}

/**
 * output = frame | frame | frame | ...
 * frame = [header][encrypted data][signature]
 * [length] = [encrypted data + signature].length
 * signature = 16 bytes
 */
TINY_LOR
static void _ChannelEncode(ChannelHandler *thiz, Channel *channel, const uint8_t *in, uint32_t inBytes)
{
    WebSocketBinaryFrameCodecContext *ctx = (WebSocketBinaryFrameCodecContext *) thiz->context;
    WebSocketFrame *frame = (WebSocketFrame *)in;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(channel);
    RETURN_IF_FAIL(in);

    LOG_D(TAG, "_ChannelEncode: %d bytes", (uint32_t) frame->length);

    do
    {
        if (RET_FAILED(WebSocketBinaryFrameEncoder_Encode(frame, ctx->outboundBinaryMessageCount, &ctx->outKey)))
        {
            break;
        }

        SocketChannel_NextWrite(channel, DATA_WEBSOCKET_FRAME, frame, 0);

        ctx->outboundBinaryMessageCount++;
    } while (false);
}
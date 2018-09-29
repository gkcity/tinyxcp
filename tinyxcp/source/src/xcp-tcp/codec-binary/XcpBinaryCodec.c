/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpBinaryCodec.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "XcpBinaryCodec.h"
#include "XcpBinaryCodecContext.h"
#include <tiny_log.h>
#include <tiny_malloc.h>
#include <channel/SocketChannel.h>
#include "frame/XcpFrameDecoder.h"
#include "frame/XcpFrameEncoder.h"

#define TAG "XcpBinaryCodec"

TINY_LOR
static TinyRet XcpBinaryCodec_Construct(ChannelHandler *thiz, HKDF *inKey, HKDF *outKey);

TINY_LOR
static TinyRet XcpBinaryCodec_Dispose(ChannelHandler *thiz);

TINY_LOR
static void XcpBinaryCodec_Delete(ChannelHandler *thiz);

TINY_LOR
static bool _ChannelRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len);

TINY_LOR
static bool _ChannelWrite(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len);

TINY_LOR
static void _ChannelDecode(ChannelHandler *thiz, Channel *channel, const uint8_t *in, uint32_t inBytes);

TINY_LOR
static void _ChannelEncode(ChannelHandler *thiz, Channel *channel, const uint8_t *in, uint32_t inBytes);

TINY_LOR
ChannelHandler * XcpBinaryCodec(HKDF *inKey, HKDF *outKey)
{
    ChannelHandler *thiz = NULL;

    do
    {
        thiz = (ChannelHandler *)tiny_malloc(sizeof(ChannelHandler));
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(XcpBinaryCodec_Construct(thiz, inKey, outKey)))
        {
            XcpBinaryCodec_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}

TINY_LOR
static void XcpBinaryCodec_Delete(ChannelHandler *thiz)
{
    XcpBinaryCodec_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
static TinyRet XcpBinaryCodec_Construct(ChannelHandler *thiz, HKDF *inKey, HKDF *outKey)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(inKey, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(outKey, TINY_RET_E_ARG_NULL);

    memset(thiz, 0, sizeof(ChannelHandler));

    strncpy(thiz->name, XcpBinaryCodec_Name, CHANNEL_HANDLER_NAME_LEN);
    thiz->onRemove = XcpBinaryCodec_Delete;
    thiz->inType = DATA_RAW;
    thiz->outType = DATA_RAW;
    thiz->channelRead = _ChannelRead;
    thiz->channelWrite = _ChannelWrite;
    thiz->context = XcpBinaryCodecContext_New(inKey, outKey);

    return TINY_RET_OK;
}

TINY_LOR
static TinyRet XcpBinaryCodec_Dispose(ChannelHandler *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->context != NULL)
    {
        XcpBinaryCodecContext_Delete(thiz->context);
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

    if (type == DATA_RAW)
    {
        _ChannelDecode(thiz, channel, data, len);
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

    if (((XcpBinaryCodecContext *) thiz->context)->started)
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
 * data = 2 + frame + signature
 * length = 2 + frame.length + 16 bytes
 */
TINY_LOR
static void _DecodeFrame(ChannelHandler *thiz, Channel *channel, const uint8_t *data, uint32_t length)
{
    XcpBinaryCodecContext *ctx = (XcpBinaryCodecContext *) thiz->context;
    XcpFrame frame;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(channel);
    RETURN_IF_FAIL(data);

    LOG_D(TAG, "_DecodeFrame: %d bytes", length);

    if (RET_FAILED(XcpFrameDecoder_Decode(&frame, data, length, ctx->inboundBinaryMessageCount++, &ctx->inKey)))
    {
        LOG_D(TAG, "FrameDecoder_Decode FAILED");
        return;
    }

    SocketChannel_NextRead(channel, DATA_RAW, frame.data, frame.length);
}

/**
 * input = frame | frame | frame | ...
 * frame = [length][encrypted data][signature]
 * length = the length of encrypted data, 2 bytes, no larger than 1024 bytes
 * signature = 16 bytes
 */
TINY_LOR
static void _ChannelDecode(ChannelHandler *thiz, Channel *channel, const uint8_t *in, uint32_t inBytes)
{
    XcpBinaryCodecContext *ctx = (XcpBinaryCodecContext *) thiz->context;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(channel);
    RETURN_IF_FAIL(in);

    ctx->started = true;

    LOG_D(TAG, "_ChannelDecode: %d bytes", inBytes);
    LOG_D(TAG, "lastBytesLength: %d", ctx->lastBytesLength);

    if (ctx->lastBytesLength > 0)
    {
        uint32_t frameLength = (uint32_t)(ctx->lastBytes[0]) + ((uint32_t)(ctx->lastBytes[1]) << 8);
        uint32_t copiedBytes = frameLength + XCP_FRAME_HEADER_LENGTH + XCP_FRAME_SIGNATURE_LENGTH - ctx->lastBytesLength;

        if (copiedBytes > inBytes)
        {
            LOG_D(TAG, "copiedBytes > inBytes");
            memcpy(ctx->lastBytes + ctx->lastBytesLength, in, inBytes);
            ctx->lastBytesLength += inBytes;
            return;
        }

        LOG_D(TAG, "frame = lastBytes + newBytes");

        memcpy(ctx->lastBytes + ctx->lastBytesLength, in, copiedBytes);
        _DecodeFrame(thiz, channel, ctx->lastBytes, XCP_FRAME_HEADER_LENGTH + frameLength + XCP_FRAME_SIGNATURE_LENGTH);

        ctx->lastBytesLength = 0;
        in += copiedBytes;
        inBytes -= copiedBytes;
    }

    while (inBytes > XCP_FRAME_HEADER_LENGTH)
    {
        uint32_t frameLength = (uint32_t)(in[0]) + ((uint32_t)(in[1]) << 8);
        if (frameLength > XCP_FRAME_DATA_MAX_LENGTH)
        {
            LOG_E(TAG, "FRAME LENGTH INVALID: %d", frameLength);
            break;
        }

        LOG_D(TAG, "FrameLength: %d", frameLength);

        if (frameLength > (inBytes - XCP_FRAME_HEADER_LENGTH))
        {
            LOG_D(TAG, "inBytes < FrameLength");
            memcpy(ctx->lastBytes, in, inBytes);
            ctx->lastBytesLength = inBytes;
            break;
        }

        LOG_D(TAG, "decode a full frame");
        _DecodeFrame(thiz, channel, in, XCP_FRAME_HEADER_LENGTH + frameLength);

        in += XCP_FRAME_HEADER_LENGTH + frameLength;

        inBytes -= XCP_FRAME_HEADER_LENGTH + frameLength;
    }
}

TINY_LOR
static void _EncodeFrame(ChannelHandler *thiz, Channel *channel, const uint8_t *data, uint32_t length)
{
    XcpBinaryCodecContext *ctx = (XcpBinaryCodecContext *) thiz->context;
    XcpFrame frame;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(channel);
    RETURN_IF_FAIL(data);

    LOG_D(TAG, "_EncodeFrame: %d bytes", length);

    if (RET_FAILED(XcpFrameEncoder_Encode(&frame, data, length, ctx->outboundBinaryMessageCount++, &ctx->outKey)))
    {
        return;
    }

    SocketChannel_NextWrite(channel, DATA_RAW, frame.data, frame.length);
}

/**
 * output = frame | frame | frame | ...
 * frame = [length][encrypted data][signature]
 * [length] = [encrypted data].length
 * signature = 16 bytes
 */
TINY_LOR
static void _ChannelEncode(ChannelHandler *thiz, Channel *channel, const uint8_t *in, uint32_t inBytes)
{
    uint32_t frameCount = inBytes / XCP_FRAME_DATA_MAX_LENGTH;
    uint32_t lastFrameSize = inBytes % XCP_FRAME_DATA_MAX_LENGTH;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(channel);
    RETURN_IF_FAIL(in);

    LOG_D(TAG, "_ChannelEncode: %d bytes", inBytes);

    for (uint32_t i = 0; i < frameCount; ++i)
    {
        _EncodeFrame(thiz, channel, in + (i * XCP_FRAME_DATA_MAX_LENGTH), XCP_FRAME_DATA_MAX_LENGTH);
    }

    if (lastFrameSize > 0)
    {
        _EncodeFrame(thiz, channel, in + (frameCount * XCP_FRAME_DATA_MAX_LENGTH), lastFrameSize);
    }
}
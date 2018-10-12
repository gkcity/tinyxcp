/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   WebSocketBinaryFrameCodecContext.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __WEB_SOCKET_BINARY_FRAME_CODEC_CONTEXT_H__
#define __WEB_SOCKET_BINARY_FRAME_CODEC_CONTEXT_H__

#include <tiny_base.h>
#include <hkdf/HKDF.h>

TINY_BEGIN_DECLS


typedef struct _WebSocketBinaryFrameCodecContext
{
    bool            started;
    int64_t         inboundBinaryMessageCount;
    int64_t         outboundBinaryMessageCount;
    HKDF            inKey;
    HKDF            outKey;
} WebSocketBinaryFrameCodecContext;

TINY_LOR
WebSocketBinaryFrameCodecContext * WebSocketBinaryFrameCodecContext_New(HKDF *inKey, HKDF *outKey);

TINY_LOR
void WebSocketBinaryFrameCodecContext_Delete(WebSocketBinaryFrameCodecContext *thiz);


TINY_END_DECLS

#endif /* __WEB_SOCKET_BINARY_FRAME_CODEC_CONTEXT_H__ */
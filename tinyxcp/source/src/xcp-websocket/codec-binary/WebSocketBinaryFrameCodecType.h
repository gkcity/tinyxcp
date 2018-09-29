/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   WebSocketBinaryFrameCodecType.h
 *
 * @remark
 *
 */

#ifndef __WEB_SOCKET_BINARY_FRAME_CODEC_TYPE_H__
#define __WEB_SOCKET_BINARY_FRAME_CODEC_TYPE_H__

#include <tiny_base.h>

TINY_BEGIN_DECLS


typedef enum _XcpFrameCodecType
{
    WEB_SOCKET_BINARY_FRAME_CODEC_UNDEFINED = -1,
    WEB_SOCKET_BINARY_FRAME_CODEC_NOT_CRYPT = 0,
    WEB_SOCKET_BINARY_FRAME_CODEC_CHACHA20_POLY1305 = 1,
    WEB_SOCKET_BINARY_FRAME_CODEC_AES_HKDF_SHA1 = 2,
} XcpFrameCodecType;


TINY_END_DECLS

#endif /* __WEB_SOCKET_BINARY_FRAME_CODEC_TYPE_H__ */
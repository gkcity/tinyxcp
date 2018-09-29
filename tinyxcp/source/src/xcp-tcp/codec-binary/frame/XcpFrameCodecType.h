/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpFrameCodecType.h
 *
 * @remark
 *
 */

#ifndef __XCP_FRAME_CODEC_TYPE_H__
#define __XCP_FRAME_CODEC_TYPE_H__

#include <tiny_base.h>

TINY_BEGIN_DECLS


typedef enum _XcpFrameCodecType
{
    XCP_FRAME_CODEC_UNDEFINED = -1,
    XCP_FRAME_CODEC_CHACHA20_POLY1305 = 0,
    XCP_FRAME_CODEC_AES_HKDF_SHA1 = 1,
} XcpFrameCodecType;


TINY_END_DECLS

#endif /* __XCP_FRAME_CODEC_TYPE_H__ */
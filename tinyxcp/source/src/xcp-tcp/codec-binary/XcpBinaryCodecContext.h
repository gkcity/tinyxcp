/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpBinaryCodecContext.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __XCP_BINARY_CODEC_CONTEXT_H__
#define __XCP_BINARY_CODEC_CONTEXT_H__

#include <tiny_base.h>
#include <hkdf/HKDF.h>
#include "frame/XcpFrame.h"

TINY_BEGIN_DECLS


typedef struct _XcpBinaryCodecContext
{
    bool            started;
    int64_t         inboundBinaryMessageCount;
    int64_t         outboundBinaryMessageCount;
    HKDF            inKey;
    HKDF            outKey;
    uint8_t         lastBytes[XCP_FRAME_MAX_LENGTH];
    uint32_t        lastBytesLength;
} XcpBinaryCodecContext;

TINY_LOR
XcpBinaryCodecContext * XcpBinaryCodecContext_New(HKDF *inKey, HKDF *outKey);

TINY_LOR
void XcpBinaryCodecContext_Delete(XcpBinaryCodecContext *thiz);


TINY_END_DECLS

#endif /* __XCP_BINARY_CODEC_CONTEXT_H__ */
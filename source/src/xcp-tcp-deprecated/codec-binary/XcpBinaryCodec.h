/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpBinaryCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __WEB_SOCKET_BINARY_FRAME_CODEC_H__
#define __WEB_SOCKET_BINARY_FRAME_CODEC_H__

#include <tiny_base.h>
#include <channel/ChannelHandler.h>
#include <hkdf/HKDF.h>

TINY_BEGIN_DECLS


#define XcpBinaryCodec_Name    "XcpBinaryCodec"

TINY_LOR
ChannelHandler * XcpBinaryCodec(HKDF *inKey, HKDF *outKey);


TINY_END_DECLS

#endif /* __WEB_SOCKET_BINARY_FRAME_CODEC_H__ */
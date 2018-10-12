/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   WebSocketBinaryFrameDecoder.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __WEB_SOCKET_BINARY_FRAME_DECODER_H__
#define __WEB_SOCKET_BINARY_FRAME_DECODER_H__

#include <tiny_base.h>
#include <hkdf/HKDF.h>
#include <codec-websocket/WebSocketFrame.h>

TINY_BEGIN_DECLS


TINY_LOR
TinyRet WebSocketBinaryFrameDecoder_Decode(WebSocketFrame *frame, int64_t nonce, HKDF *key);


TINY_END_DECLS

#endif /* __WEB_SOCKET_BINARY_FRAME_DECODER_H__ */
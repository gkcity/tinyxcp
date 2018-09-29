/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   XcpFrameEncoder.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __XCP_FRAME_ENCODER_H__
#define __XCP_FRAME_ENCODER_H__

#include <tiny_base.h>
#include <hkdf/HKDF.h>
#include "XcpFrame.h"

TINY_BEGIN_DECLS


TINY_LOR
TinyRet XcpFrameEncoder_Encode(XcpFrame *frame, const uint8_t *data, uint32_t length, int64_t nonce, HKDF *key);


TINY_END_DECLS

#endif /* __XCP_FRAME_ENCODER_H__ */
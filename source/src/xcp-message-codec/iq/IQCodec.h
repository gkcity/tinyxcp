/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   IQCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __IQ_CODEC_H__
#define __IQ_CODEC_H__

#include <tiny_base.h>
#include <JsonObject.h>
#include <XcpMessage.h>

TINY_BEGIN_DECLS


TINY_LOR
TinyRet IQCodec_Encode(JsonObject *root, IQ *iq);

TINY_LOR
TinyRet IQCodec_Decode(IQ* iq, JsonObject *object);


TINY_END_DECLS

#endif /* __IQ_CODEC_H__  */
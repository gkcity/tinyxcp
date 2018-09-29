/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   IQErrorCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __IQ_ERROR_CODEC_H__
#define __IQ_ERROR_CODEC_H__

#include <tiny_base.h>
#include <JsonObject.h>
#include <iq/IQError.h>

TINY_BEGIN_DECLS


TINY_LOR
TinyRet IQErrorCodec_Encode(JsonObject *root, IQError *error);

TINY_LOR
TinyRet IQErrorCodec_Decode(IQError* error, JsonObject *object);


TINY_END_DECLS

#endif /* __IQ_ERROR_CODEC_H__  */
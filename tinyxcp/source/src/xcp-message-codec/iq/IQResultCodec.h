/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   IQResultCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __IQ_RESULT_CODEC_H__
#define __IQ_RESULT_CODEC_H__

#include <tiny_base.h>
#include <JsonObject.h>
#include <iq/IQResult.h>

TINY_BEGIN_DECLS


TINY_LOR
TinyRet IQResultCodec_Encode(JsonObject *root, IQResult *query);

TINY_LOR
TinyRet IQResultCodec_Decode(IQResult* result, JsonObject *object);


TINY_END_DECLS

#endif /* __IQ_RESULT_CODEC_H__  */
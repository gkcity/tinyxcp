/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   IQQueryCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __IQ_QUERY_CODEC_H__
#define __IQ_QUERY_CODEC_H__

#include <tiny_base.h>
#include <JsonObject.h>
#include <iq/IQQuery.h>

TINY_BEGIN_DECLS


TINY_LOR
TinyRet IQQueryCodec_Encode(JsonObject *root, IQQuery *query);

TINY_LOR
TinyRet IQQueryCodec_Decode(IQQuery* query, JsonObject *object);


TINY_END_DECLS

#endif /* __IQ_QUERY_CODEC_H__  */
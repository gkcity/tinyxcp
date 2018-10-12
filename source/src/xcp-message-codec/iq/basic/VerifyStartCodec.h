/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   VerifyStartCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __VerifyStartCodec_H__
#define __VerifyStartCodec_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <JsonObject.h>
#include <iq/basic/VerifyStart.h>

TINY_BEGIN_DECLS


TinyRet VerifyStartCodec_EncodeQuery(JsonObject *content, QueryVerifyStart *query);

TinyRet VerifyStartCodec_DecodeResult(ResultVerifyStart *result, JsonObject *content);


TINY_END_DECLS

#endif /* __VerifyStartCodec_H__  */

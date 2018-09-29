/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   InvokeActionCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __InvokeActionCodec_H__
#define __InvokeActionCodec_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <JsonObject.h>
#include <iq/basic/InvokeAction.h>

TINY_BEGIN_DECLS


TinyRet InvokeActionCodec_DecodeQuery(QueryInvokeAction *query, JsonObject *content);

TinyRet InvokeActionCodec_EncodeResult(JsonObject *content, ResultInvokeAction *result);


TINY_END_DECLS

#endif /* __InvokeActionCodec_H__  */

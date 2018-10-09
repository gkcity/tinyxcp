/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   GetAccessKeyCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __GetAccessKeyCodec_H__
#define __GetAccessKeyCodec_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <JsonObject.h>
#include <iq/basic/GetAccessKey.h>

TINY_BEGIN_DECLS


TinyRet GetAccessKeyCodec_DecodeResult(ResultGetAccessKey *result, JsonObject *content);


TINY_END_DECLS

#endif /* __GetAccessKeyCodec_H__  */

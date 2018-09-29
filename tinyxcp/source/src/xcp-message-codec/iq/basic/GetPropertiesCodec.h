/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   GetPropertiesCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __GetPropertiesCodec_H__
#define __GetPropertiesCodec_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <JsonObject.h>
#include <iq/basic/GetProperties.h>

TINY_BEGIN_DECLS


TinyRet GetPropertiesCodec_DecodeQuery(QueryGetProperties *getProperties, JsonObject *content);

TinyRet GetPropertiesCodec_EncodeResult(JsonObject *content, ResultGetProperties *getProperties);


TINY_END_DECLS

#endif /* __GetPropertiesCodec_H__  */

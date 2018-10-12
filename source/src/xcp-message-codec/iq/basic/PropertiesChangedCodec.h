/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   PropertiesChangedCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __PropertiesChangedCodec_H__
#define __PropertiesChangedCodec_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <JsonObject.h>
#include <iq/basic/PropertiesChanged.h>

TINY_BEGIN_DECLS


TinyRet PropertiesChangedCodec_EncodeQuery(JsonObject *content, QueryPropertiesChanged *propertiesChanged);


TinyRet PropertiesChangedCodec_DecodeResult(ResultPropertiesChanged *propertiesChanged, JsonObject *content);


TINY_END_DECLS

#endif /* __PropertiesChangedCodec_H__  */

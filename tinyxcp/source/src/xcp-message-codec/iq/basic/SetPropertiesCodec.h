/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   SetPropertiesCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __SetPropertiesCodec_H__
#define __SetPropertiesCodec_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <JsonObject.h>
#include <iq/basic/SetProperties.h>

TINY_BEGIN_DECLS


TinyRet SetPropertiesCodec_DecodeQuery(QuerySetProperties *setProperties, JsonObject *content);

TinyRet SetPropertiesCodec_EncodeResult(JsonObject *content, ResultSetProperties *setProperties);


TINY_END_DECLS

#endif /* __SetPropertiesCodec_H__  */

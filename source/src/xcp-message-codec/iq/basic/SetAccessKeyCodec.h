/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   SetAccessKeyCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __SetAccessKeyCodec_H__
#define __SetAccessKeyCodec_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <JsonObject.h>
#include <iq/basic/SetAccessKey.h>

TINY_BEGIN_DECLS


TinyRet SetAccessKeyCodec_EncodeQuery(JsonObject *content, QuerySetAccessKey *query);



TINY_END_DECLS

#endif /* __SetAccessKeyCodec_H__  */

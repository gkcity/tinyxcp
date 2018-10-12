/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   EventOccurredCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __EventOccurredCodec_H__
#define __EventOccurredCodec_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <JsonObject.h>
#include <iq/basic/EventOccurred.h>

TINY_BEGIN_DECLS


TinyRet EventOccurredCodec_EncodeQuery(JsonObject *content, QueryEventOccurred *eventOccurred);


TINY_END_DECLS

#endif /* __EventOccurredCodec_H__  */

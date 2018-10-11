/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   InitializeCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __InitializeCodec_H__
#define __InitializeCodec_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <JsonObject.h>
#include <iq/basic/Initialize.h>

TINY_BEGIN_DECLS


TinyRet InitializeCodec_EncodeQuery(JsonObject *content, QueryInitialize *initialize);



TINY_END_DECLS

#endif /* __InitializeCodec_H__  */

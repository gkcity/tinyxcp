/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   VerifyFinishCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __VerifyFinishCodec_H__
#define __VerifyFinishCodec_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <JsonObject.h>
#include <iq/basic/VerifyFinish.h>

TINY_BEGIN_DECLS


TinyRet VerifyFinishCodec_EncodeQuery(JsonObject *content, QueryVerifyFinish *verifyFinish);



TINY_END_DECLS

#endif /* __VerifyFinishCodec_H__  */

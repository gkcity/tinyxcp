/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   VerifyFinish.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __VerifyFinish_H__
#define __VerifyFinish_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <constant/iot_constant.h>
#include <XcpConstant.h>

TINY_BEGIN_DECLS


typedef struct _QueryVerifyFinish
{
    char                udid[IOT_UDID_LENGTH];
    char                signature[XCP_SIGNATURE_LENGTH];
    uint8_t             codec;
} QueryVerifyFinish;

TinyRet QueryVerifyFinish_Construct(QueryVerifyFinish *thiz);
void QueryVerifyFinish_Dispose(QueryVerifyFinish *thiz);


TINY_END_DECLS

#endif /* __VerifyFinish_H__  */

/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   VerifyStart.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __VerifyStart_H__
#define __VerifyStart_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <XcpConstant.h>

TINY_BEGIN_DECLS


typedef struct _QueryVerifyStart
{
    char        publicKey[XCP_PUBLIC_KEY_LENGTH];
} QueryVerifyStart;

TinyRet QueryVerifyStart_Construct(QueryVerifyStart *thiz);
void QueryVerifyStart_Dispose(QueryVerifyStart *thiz);

typedef struct _ResultVerifyStart
{
    char        publicKey[XCP_PUBLIC_KEY_LENGTH];
    char        signature[XCP_SIGNATURE_LENGTH];
} ResultVerifyStart;

TinyRet ResultVerifyStart_Construct(ResultVerifyStart *thiz);
void ResultVerifyStart_Dispose(ResultVerifyStart *thiz);


TINY_END_DECLS

#endif /* __VerifyStart_H__  */

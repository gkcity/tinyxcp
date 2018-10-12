/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   SetAccessKey.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __SetAccessKey_H__
#define __SetAccessKey_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <XcpConstant.h>

TINY_BEGIN_DECLS


/**
 * Query
 */
typedef struct _QuerySetAccessKey
{
    char  key[XCP_ACCESS_KEY_LEN];
} QuerySetAccessKey;

TinyRet QuerySetAccessKey_Construct(QuerySetAccessKey *thiz);
void QuerySetAccessKey_Dispose(QuerySetAccessKey *thiz);

/**
 * Result
 */


TINY_END_DECLS

#endif /* __SetAccessKey_H__  */

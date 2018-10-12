/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   GetAccessKey.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __GetAccessKey_H__
#define __GetAccessKey_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <XcpConstant.h>

TINY_BEGIN_DECLS


/**
 * Query
 */


/**
 * Result
 */

typedef struct _ResultGetAccessKey
{
    char  key[XCP_ACCESS_KEY_LEN];
} ResultGetAccessKey;

TinyRet ResultGetAccessKey_Construct(ResultGetAccessKey *thiz);
void ResultGetAccessKey_Dispose(ResultGetAccessKey *thiz);


TINY_END_DECLS

#endif /* __GetAccessKey_H__  */

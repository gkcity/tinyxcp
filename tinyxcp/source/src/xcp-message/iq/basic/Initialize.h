/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   Initialize.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __Initialize_H__
#define __Initialize_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <XcpConstant.h>

TINY_BEGIN_DECLS


typedef struct _QueryInitialize
{
    char version[XCP_INITIALIZE_VERSION_LEN];
    char authentication[XCP_AUTHENTICATION_LEN];
} QueryInitialize;

TinyRet QueryInitialize_Construct(QueryInitialize *thiz);
void QueryInitialize_Dispose(QueryInitialize *thiz);


TINY_END_DECLS

#endif /* __Initialize_H__  */

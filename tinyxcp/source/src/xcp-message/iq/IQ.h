/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   IQ.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __IQ_H__
#define __IQ_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <TinyList.h>
#include "IQQuery.h"
#include "IQResult.h"
#include "IQError.h"

TINY_BEGIN_DECLS


typedef enum _IQType
{
    IQ_TYPE_UNDEFINED           = 0x00,
    IQ_TYPE_QUERY               = 0x01,
    IQ_TYPE_RESULT              = 0x02,
    IQ_TYPE_ERROR               = 0x03,
} IQType;

#define MESSAGE_ID_LENGTH       64

typedef struct _IQ
{
    char                id[MESSAGE_ID_LENGTH + 1];
    IQType              type;
    union _
    {
        IQQuery         query;
        IQResult        result;
        IQError         error;
    } content;
} IQ;

TINY_LOR
TinyRet IQ_InitializeQuery(IQ *thiz, IQMethod method);

TINY_LOR
void IQ_Dispose(IQ *thiz);


TINY_END_DECLS

#endif /* __IQ_H__  */
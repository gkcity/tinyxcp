/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   EventOccurred.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __EventOccurred_H__
#define __EventOccurred_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <operation/EventOperation.h>

TINY_BEGIN_DECLS


/**
 * Query
 */
typedef struct _QueryEventOccurred
{
    EventOperation      operation;
} QueryEventOccurred;

TinyRet QueryEventOccurred_Construct(QueryEventOccurred *thiz);
void QueryEventOccurred_Dispose(QueryEventOccurred *thiz);

/**
 * Result
 */

TINY_END_DECLS

#endif /* __EventOccurred_H__  */

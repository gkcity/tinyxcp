/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   EventOccurred.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "EventOccurred.h"

TinyRet QueryEventOccurred_Construct(QueryEventOccurred *thiz)
{
    return EventOperation_Construct(&thiz->operation);
}

void QueryEventOccurred_Dispose(QueryEventOccurred *thiz)
{
    EventOperation_Dispose(&thiz->operation);
}

/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   IQ.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "IQ.h"

TINY_LOR
void IQ_Dispose(IQ *thiz)
{
    switch (thiz->type)
    {
        case IQ_TYPE_QUERY:
            IQQuery_Dispose(&thiz->content.query);
            break;

        case IQ_TYPE_RESULT:
            IQResult_Dispose(&thiz->content.result);
            break;

        case IQ_TYPE_ERROR:
            IQError_Dispose(&thiz->content.error);
            break;

        default:
            break;
    }
}
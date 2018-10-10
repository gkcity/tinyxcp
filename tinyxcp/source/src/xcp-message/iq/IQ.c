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
TinyRet IQ_InitializeQuery(IQ *thiz, const char *id, IQMethod method)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(id, TINY_RET_E_ARG_NULL);

    thiz->type = IQ_TYPE_QUERY;
    thiz->content.query.method = method;
    strncpy(thiz->id, id, MESSAGE_ID_LENGTH);
    return IQQuery_Initialize(&thiz->content.query);
}

TINY_LOR
TinyRet IQ_InitializeResult(IQ *thiz, const char *id, IQMethod method)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(id, TINY_RET_E_ARG_NULL);

    thiz->type = IQ_TYPE_RESULT;
    thiz->content.result.method = method;
    strncpy(thiz->id, id, MESSAGE_ID_LENGTH);
    return IQResult_Initialize(&thiz->content.result);
}

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
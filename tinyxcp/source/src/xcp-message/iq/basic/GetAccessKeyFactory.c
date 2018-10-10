/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   QueryGetAccessKeyFactory.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "GetAccessKeyFactory.h"

TINY_LOR
XcpMessage * QueryGetAccessKey_New(const char *id)
{
    XcpMessage *thiz = NULL;

    do
    {
        thiz = XcpMessage_New();
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(IQ_InitializeQuery(&thiz->iq, id, IQ_METHOD_GET_ACCESS_KEY)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}
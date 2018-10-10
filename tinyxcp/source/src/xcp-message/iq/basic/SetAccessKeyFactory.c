/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   SetAccessKeyFactory.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "SetAccessKeyFactory.h"

TINY_LOR
XcpMessage * QuerySetAccessKey_New(const char *id, const char *key)
{
    XcpMessage *thiz = NULL;

    RETURN_VAL_IF_FAIL(key, NULL);

    do
    {
        thiz = XcpMessage_New();
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(IQ_InitializeQuery(&thiz->iq, id, IQ_METHOD_SET_ACCESS_KEY)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
            break;
        }

        strncpy(thiz->iq.content.query.content.setAccessKey.key, key, XCP_ACCESS_KEY_LEN);
    } while (false);

    return thiz;
}
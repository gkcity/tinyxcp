/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   XcpMessage.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_malloc.h>
#include "XcpMessage.h"

TINY_LOR
static TinyRet XcpMessage_Construct(XcpMessage *thiz)
{
    memset(thiz, 0, sizeof(XcpMessage));
    return TINY_RET_OK;
}

static void XcpMessage_Dispose(XcpMessage *thiz)
{
    RETURN_IF_FAIL(thiz);
}

TINY_LOR
XcpMessage * XcpMessage_New(void)
{
    XcpMessage *thiz = NULL;

    do
    {
        thiz = (XcpMessage *)tiny_malloc(sizeof(XcpMessage));
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(XcpMessage_Construct(thiz)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}

TINY_LOR
void XcpMessage_Delete(XcpMessage *thiz)
{
    XcpMessage_Dispose(thiz);
    tiny_free(thiz);
}
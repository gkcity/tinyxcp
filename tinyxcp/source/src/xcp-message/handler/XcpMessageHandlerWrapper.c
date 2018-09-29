/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpMessageHandlerWrapper.c
 *
 * @remark
 *
 */

#include <tiny_log.h>
#include <tiny_malloc.h>
#include "XcpMessageHandlerWrapper.h"

#define TAG "XcpMessageHandlerWrapper"

TINY_LOR
static TinyRet XcpMessageHandlerWrapper_Construct(XcpMessageHandlerWrapper *thiz, XcpMessageHandler handler, void *ctx)
{
    memset(thiz, 0, sizeof(XcpMessageHandlerWrapper));
    thiz->handler = handler;
    thiz->ctx = ctx;

    return TINY_RET_OK;
}

TINY_LOR
static void XcpMessageHandlerWrapper_Dispose(XcpMessageHandlerWrapper *thiz)
{
    RETURN_IF_FAIL(thiz);
}

TINY_LOR
XcpMessageHandlerWrapper * XcpMessageHandlerWrapper_New(XcpMessageHandler handler, void *ctx)
{
    XcpMessageHandlerWrapper *thiz = NULL;

    do
    {
        thiz = (XcpMessageHandlerWrapper *)tiny_malloc(sizeof(XcpMessageHandlerWrapper));
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(XcpMessageHandlerWrapper_Construct(thiz, handler, ctx)))
        {
            LOG_E(TAG, "XcpMessageHandlerWrapper_Construct FAILED");
            XcpMessageHandlerWrapper_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}

TINY_LOR
void XcpMessageHandlerWrapper_Delete(XcpMessageHandlerWrapper *thiz)
{
    XcpMessageHandlerWrapper_Dispose(thiz);
    tiny_free(thiz);
}

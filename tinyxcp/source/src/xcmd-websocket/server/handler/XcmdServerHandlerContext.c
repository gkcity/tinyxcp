/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcmdServerHandlerContext.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_snprintf.h>
#include <tiny_log.h>
#include "XcmdServerHandlerContext.h"

#define TAG     "XcmdServerHandlerContext"

TINY_LOR
static void _OnHandlerRemove (void * data, void *ctx)
{
    XcpMessageHandlerWrapper *wrapper = (XcpMessageHandlerWrapper *)data;
    XcpMessageHandlerWrapper_Delete(wrapper);
}

TINY_LOR
static TinyRet XcmdServerHandlerContext_Construct(XcmdServerHandlerContext *thiz)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        memset(thiz, 0, sizeof(XcmdServerHandlerContext));
        thiz->messageIndex = 1;

        ret = TinyMap_Construct(&thiz->handlers);
        if (RET_FAILED(ret))
        {
            break;
        }
        TinyMap_SetDeleteListener(&thiz->handlers, _OnHandlerRemove, NULL);
    } while (0);

    return ret;
}

TINY_LOR
static void XcmdServerHandlerContext_Dispose(XcmdServerHandlerContext *thiz)
{
    RETURN_IF_FAIL(thiz);

    TinyMap_Dispose(&thiz->handlers);
}

TINY_LOR
XcmdServerHandlerContext * XcmdServerHandlerContext_New(void)
{
    XcmdServerHandlerContext *thiz = NULL;

    do
    {
        thiz = (XcmdServerHandlerContext *)tiny_malloc(sizeof(XcmdServerHandlerContext));
        if (thiz == NULL)
        {
            LOG_E(TAG, "tiny_malloc failed");
            break;
        }

        if (RET_FAILED(XcmdServerHandlerContext_Construct(thiz)))
        {
            LOG_E(TAG, "XcmdServerHandlerContext_Construct failed");
            XcmdServerHandlerContext_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}

TINY_LOR
void XcmdServerHandlerContext_Delete(XcmdServerHandlerContext *thiz)
{
    XcmdServerHandlerContext_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
TinyRet XcmdServerHandlerContext_AddHandler(XcmdServerHandlerContext *thiz, const char *id, XcpMessageHandler handler, void *ctx)
{
    XcpMessageHandlerWrapper *wrapper = NULL;

    wrapper = XcpMessageHandlerWrapper_New(handler, ctx);
    if (wrapper == NULL)
    {
        return TINY_RET_E_OUT_OF_MEMORY;
    }

    return TinyMap_Insert(&thiz->handlers, id, wrapper);
}

TINY_LOR
TinyRet XcmdServerHandlerContext_Handle(XcmdServerHandlerContext *thiz, XcpMessage *message)
{
    XcpMessageHandlerWrapper *wrapper = NULL;

    wrapper = (XcpMessageHandlerWrapper *)TinyMap_GetValue(&thiz->handlers, message->iq.id);
    if (wrapper == NULL)
    {
        return TINY_RET_E_NOT_IMPLEMENTED;
    }

    wrapper->handler(message, wrapper->ctx);

    return TinyMap_Erase(&thiz->handlers, message->iq.id);
}

TINY_LOR
const char *XcmdServerHandlerContext_NextId(XcmdServerHandlerContext *thiz)
{
    tiny_snprintf(thiz->messageId, MESSAGE_ID_LENGTH, "%d", thiz->messageIndex++);
    return thiz->messageId;
}

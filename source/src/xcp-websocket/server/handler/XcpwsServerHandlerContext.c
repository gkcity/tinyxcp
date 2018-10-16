/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpwsServerHandlerContext.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_snprintf.h>
#include <tiny_log.h>
#include "XcpwsServerHandlerContext.h"

#define TAG     "XcpwsServerHandlerContext"

TINY_LOR
static void _OnHandlerRemove (void * data, void *ctx)
{
    XcpMessageHandlerWrapper *wrapper = (XcpMessageHandlerWrapper *)data;
    XcpMessageHandlerWrapper_Delete(wrapper);
}

TINY_LOR
static TinyRet XcpwsServerHandlerContext_Construct(XcpwsServerHandlerContext *thiz, XcpwsServerContext *data)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        memset(thiz, 0, sizeof(XcpwsServerHandlerContext));
        thiz->messageIndex = 1;
        thiz->data = data;

        ret = TinyMap_Construct(&thiz->handlers, _OnHandlerRemove, NULL);
        if (RET_FAILED(ret))
        {
            //LOG_E(TAG, "TinyMap_Construct FAILED: %s", tiny_ret_to_str(ret));
            break;
        }
    } while (0);

    return ret;
}

TINY_LOR
static void XcpwsServerHandlerContext_Dispose(XcpwsServerHandlerContext *thiz)
{
    RETURN_IF_FAIL(thiz);

    TinyMap_Dispose(&thiz->handlers);
}

TINY_LOR
XcpwsServerHandlerContext * XcpwsServerHandlerContext_New(XcpwsServerContext *data)
{
    XcpwsServerHandlerContext *thiz = NULL;

    do
    {
        thiz = (XcpwsServerHandlerContext *)tiny_malloc(sizeof(XcpwsServerHandlerContext));
        if (thiz == NULL)
        {
            LOG_E(TAG, "tiny_malloc failed");
            break;
        }

        if (RET_FAILED(XcpwsServerHandlerContext_Construct(thiz, data)))
        {
            LOG_E(TAG, "XcpwsServerHandlerContext_Construct failed");
            XcpwsServerHandlerContext_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}

TINY_LOR
void XcpwsServerHandlerContext_Delete(XcpwsServerHandlerContext *thiz)
{
    XcpwsServerHandlerContext_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
TinyRet XcpwsServerHandlerContext_AddHandler(XcpwsServerHandlerContext *thiz, const char *id, XcpMessageHandler handler, void *ctx)
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
TinyRet XcpwsServerHandlerContext_Handle(XcpwsServerHandlerContext *thiz, XcpMessage *message)
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
const char *XcpwsServerHandlerContext_NextId(XcpwsServerHandlerContext *thiz)
{
    tiny_snprintf(thiz->messageId, MESSAGE_ID_LENGTH, "%d", thiz->messageIndex++);
    return thiz->messageId;
}

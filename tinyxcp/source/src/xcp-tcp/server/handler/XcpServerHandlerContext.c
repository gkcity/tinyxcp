/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpServerHandlerContext.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_snprintf.h>
#include <tiny_log.h>
#include "XcpServerHandlerContext.h"

#define TAG     "XcpServerHandlerContext"

TINY_LOR
static void _OnHandlerRemove (void * data, void *ctx)
{
    XcpMessageHandlerWrapper *wrapper = (XcpMessageHandlerWrapper *)data;
    XcpMessageHandlerWrapper_Delete(wrapper);
}

TINY_LOR
static TinyRet XcpServerHandlerContext_Construct(XcpServerHandlerContext *thiz, Device *device)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        memset(thiz, 0, sizeof(XcpServerHandlerContext));
        thiz->messageIndex = 1;
        thiz->device = device;

        ret = TinyMap_Construct(&thiz->handlers);
        if (RET_FAILED(ret))
        {
            //LOG_E(TAG, "TinyMap_Construct FAILED: %s", tiny_ret_to_str(ret));
            break;
        }
        TinyMap_SetDeleteListener(&thiz->handlers, _OnHandlerRemove, NULL);
    } while (0);

    return ret;
}

TINY_LOR
static void XcpServerHandlerContext_Dispose(XcpServerHandlerContext *thiz)
{
    RETURN_IF_FAIL(thiz);

    TinyMap_Dispose(&thiz->handlers);
}

TINY_LOR
XcpServerHandlerContext * XcpServerHandlerContext_New(Device *device)
{
    XcpServerHandlerContext *thiz = NULL;

    do
    {
        thiz = (XcpServerHandlerContext *)tiny_malloc(sizeof(XcpServerHandlerContext));
        if (thiz == NULL)
        {
            LOG_E(TAG, "tiny_malloc failed");
            break;
        }

        if (RET_FAILED(XcpServerHandlerContext_Construct(thiz, device)))
        {
            LOG_E(TAG, "XcpServerHandlerContext_Construct failed");
            XcpServerHandlerContext_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}

TINY_LOR
void XcpServerHandlerContext_Delete(XcpServerHandlerContext *thiz)
{
    XcpServerHandlerContext_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
TinyRet XcpServerHandlerContext_AddHandler(XcpServerHandlerContext *thiz, const char *id, XcpMessageHandler handler, void *ctx)
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
TinyRet XcpServerHandlerContext_Handle(XcpServerHandlerContext *thiz, XcpMessage *message)
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
const char *XcpServerHandlerContext_NextId(XcpServerHandlerContext *thiz)
{
    tiny_snprintf(thiz->messageId, MESSAGE_ID_LENGTH, "%d", thiz->messageIndex++);
    return thiz->messageId;
}

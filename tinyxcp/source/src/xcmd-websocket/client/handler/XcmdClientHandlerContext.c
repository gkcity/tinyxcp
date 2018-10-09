/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcmdClientHandlerContext.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_snprintf.h>
#include <tiny_log.h>
#include <channel/SocketChannel.h>
#include "codec-binary/WebSocketBinaryFrameCodecType.h"
#include "codec-message/CustomDataType.h"
#include "XcmdClientHandlerContext.h"

#define TAG     "XcmdClientHandlerContext"

TINY_LOR
static void _OnHandlerRemove (void * data, void *ctx)
{
    XcpMessageHandlerWrapper *wrapper = (XcpMessageHandlerWrapper *)data;
    XcpMessageHandlerWrapper_Delete(wrapper);
}

TINY_LOR
static TinyRet XcmdClientHandlerContext_Construct(XcmdClientHandlerContext *thiz)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        memset(thiz, 0, sizeof(XcmdClientHandlerContext));
        thiz->messageIndex = 1;

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
static void XcmdClientHandlerContext_Dispose(XcmdClientHandlerContext *thiz)
{
    RETURN_IF_FAIL(thiz);

    TinyMap_Dispose(&thiz->handlers);
}

TINY_LOR
XcmdClientHandlerContext * XcmdClientHandlerContext_New()
{
    XcmdClientHandlerContext *thiz = NULL;

    do
    {
        thiz = (XcmdClientHandlerContext *)tiny_malloc(sizeof(XcmdClientHandlerContext));
        if (thiz == NULL)
        {
            LOG_E(TAG, "tiny_malloc failed");
            break;
        }

        if (RET_FAILED(XcmdClientHandlerContext_Construct(thiz)))
        {
            LOG_E(TAG, "XcmdClientHandlerContext_Construct failed");
            XcmdClientHandlerContext_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}

TINY_LOR
void XcmdClientHandlerContext_Delete(XcmdClientHandlerContext *thiz)
{
    XcmdClientHandlerContext_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
TinyRet XcmdClientHandlerContext_AddHandler(XcmdClientHandlerContext *thiz, const char *id, XcpMessageHandler handler, void *ctx)
{
    XcpMessageHandlerWrapper *wrapper = NULL;

    wrapper = XcpMessageHandlerWrapper_New(handler, ctx);
    if (wrapper == NULL)
    {
	LOG_E(TAG, "XcpMessageHandlerWrapper_New FAILED");
        return TINY_RET_E_OUT_OF_MEMORY;
    }

    return TinyMap_Insert(&thiz->handlers, id, wrapper);
}

TINY_LOR
TinyRet XcmdClientHandlerContext_Handle(XcmdClientHandlerContext *thiz, XcpMessage *message)
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
const char *XcmdClientHandlerContext_NextId(void *context)
{
    XcmdClientHandlerContext *thiz = (XcmdClientHandlerContext *)context;
    tiny_snprintf(thiz->messageId, MESSAGE_ID_LENGTH, "%d", thiz->messageIndex++);
    return thiz->messageId;
}

TINY_LOR
TinyRet XcpClientHandlerContext_SendQuery(void *context, XcpMessage *query, XcpMessageHandler handler, void *ctx)
{
    TinyRet ret = TINY_RET_OK;
    XcmdClientHandlerContext *thiz = (XcmdClientHandlerContext *)context;

    ret = XcmdClientHandlerContext_AddHandler(context, query->iq.id, handler, ctx);
    if (RET_SUCCEEDED(ret))
    {
        SocketChannel_StartWrite(thiz->channel, DATA_XCP_MESSAGE, query, 0);
    }

    return ret;
}

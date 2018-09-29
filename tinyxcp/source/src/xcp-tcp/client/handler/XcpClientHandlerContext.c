/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpClientHandlerContext.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_snprintf.h>
#include <tiny_log.h>
#include <codec-message/CustomDataType.h>
#include <codec-binary/frame/XcpFrameCodecType.h>
#include <channel/SocketChannel.h>
#include "XcpClientHandlerContext.h"

#define TAG     "XcpClientHandlerContext"

TINY_LOR
static void _OnHandlerRemove (void * data, void *ctx)
{
    XcpMessageHandlerWrapper *wrapper = (XcpMessageHandlerWrapper *)data;
    XcpMessageHandlerWrapper_Delete(wrapper);
}

TINY_LOR
static TinyRet XcpClientHandlerContext_Construct(XcpClientHandlerContext *thiz, Device *device, const char *serverLTPK)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        memset(thiz, 0, sizeof(XcpClientHandlerContext));
        thiz->messageIndex = 1;
        thiz->device = device;

        ret = TinyMap_Construct(&thiz->handlers);
        if (RET_FAILED(ret))
        {
            //LOG_E(TAG, "TinyMap_Construct FAILED: %s", tiny_ret_to_str(ret));
            break;
        }
        TinyMap_SetDeleteListener(&thiz->handlers, _OnHandlerRemove, NULL);

        thiz->verifier = XcpClientVerifier_New(serverLTPK,
                                               device,
                                               XcpClientHandlerContext_NextId,
                                               XcpClientHandlerContext_SendQuery,
                                               XCP_FRAME_CODEC_CHACHA20_POLY1305);
        if (thiz->verifier == NULL)
        {
            ret = TINY_RET_E_NEW;
            //LOG_E(TAG, "XcpClientVerifier_New FAILED: %s", tiny_ret_to_str(ret));
            break;
        }
    } while (0);

    return ret;
}

TINY_LOR
static void XcpClientHandlerContext_Dispose(XcpClientHandlerContext *thiz)
{
    RETURN_IF_FAIL(thiz);

    TinyMap_Dispose(&thiz->handlers);

    if (thiz->verifier != NULL)
    {
        XcpClientVerifier_Delete(thiz->verifier);
        thiz->verifier = NULL;
    }
}

#define SERVER_LTPK     "/8meBcfecxNl7pMIO0Zxbhx70A4DSGio7C2H7VzZLB8="

TINY_LOR
XcpClientHandlerContext * XcpClientHandlerContext_New(Device *device)
{
    XcpClientHandlerContext *thiz = NULL;

    do
    {
        thiz = (XcpClientHandlerContext *)tiny_malloc(sizeof(XcpClientHandlerContext));
        if (thiz == NULL)
        {
            LOG_E(TAG, "tiny_malloc failed");
            break;
        }

        if (RET_FAILED(XcpClientHandlerContext_Construct(thiz, device, SERVER_LTPK)))
        {
            LOG_E(TAG, "XcpClientHandlerContext_Construct failed");
            XcpClientHandlerContext_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}

TINY_LOR
void XcpClientHandlerContext_Delete(XcpClientHandlerContext *thiz)
{
    XcpClientHandlerContext_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
TinyRet XcpClientHandlerContext_AddHandler(XcpClientHandlerContext *thiz, const char *id, XcpMessageHandler handler, void *ctx)
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
TinyRet XcpClientHandlerContext_Handle(XcpClientHandlerContext *thiz, XcpMessage *message)
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
const char *XcpClientHandlerContext_NextId(void *context)
{
    XcpClientHandlerContext *thiz = (XcpClientHandlerContext *)context;
    tiny_snprintf(thiz->messageId, MESSAGE_ID_LENGTH, "%d", thiz->messageIndex++);
    return thiz->messageId;
}

TINY_LOR
TinyRet XcpClientHandlerContext_SendQuery(void *context, XcpMessage *query, XcpMessageHandler handler, void *ctx)
{
    TinyRet ret = TINY_RET_OK;
    XcpClientHandlerContext *thiz = (XcpClientHandlerContext *)context;

    ret = XcpClientHandlerContext_AddHandler(context, query->iq.id, handler, ctx);
    if (RET_SUCCEEDED(ret))
    {
        SocketChannel_StartWrite(thiz->channel, DATA_XCP_MESSAGE, query, 0);
    }

    return ret;
}

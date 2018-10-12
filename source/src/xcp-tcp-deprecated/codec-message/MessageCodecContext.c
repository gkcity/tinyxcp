/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   MessageCodecContext.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_malloc.h>
#include "MessageCodecContext.h"

TINY_LOR
static TinyRet MessageCodecContext_Construct(MessageCodecContext *thiz, Device *device)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(device, TINY_RET_E_ARG_NULL);

    memset(thiz, 0, sizeof(MessageCodecContext));
    thiz->device = device;

    ByteBuffer_Construct(&thiz->buffer, MESSAGE_BUFFER_SIZE);

    return TINY_RET_OK;
}

TINY_LOR
static TinyRet MessageCodecContext_Dispose(MessageCodecContext *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    ByteBuffer_Dispose(&thiz->buffer);

    memset(thiz, 0, sizeof(MessageCodecContext));

    return TINY_RET_OK;
}

TINY_LOR
MessageCodecContext * MessageCodecContext_New(Device *host)
{
    MessageCodecContext *thiz = NULL;

    do
    {
        thiz = tiny_malloc(sizeof(MessageCodecContext));
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(MessageCodecContext_Construct(thiz, host)))
        {
            MessageCodecContext_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}

TINY_LOR
void MessageCodecContext_Delete(MessageCodecContext *thiz)
{
    MessageCodecContext_Dispose(thiz);
    tiny_free(thiz);
}
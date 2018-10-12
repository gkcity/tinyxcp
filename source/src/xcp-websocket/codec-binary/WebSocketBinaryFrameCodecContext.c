/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   WebSocketBinaryFrameCodecContext.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_malloc.h>
#include "WebSocketBinaryFrameCodecContext.h"

TINY_LOR
WebSocketBinaryFrameCodecContext * WebSocketBinaryFrameCodecContext_New(HKDF *inKey, HKDF *outKey)
{
    WebSocketBinaryFrameCodecContext *thiz = NULL;

    do
    {
        thiz = tiny_malloc(sizeof(WebSocketBinaryFrameCodecContext));
        if (thiz == NULL)
        {
            break;
        }

        memcpy(&thiz->inKey, inKey->value, inKey->length);
        thiz->inKey.length = inKey->length;

        memcpy(&thiz->outKey, outKey->value, outKey->length);
        thiz->outKey.length = outKey->length;

        thiz->started = false;
        thiz->inboundBinaryMessageCount = 0;
        thiz->outboundBinaryMessageCount = 0;
    } while (0);

    return thiz;
}

TINY_LOR
void WebSocketBinaryFrameCodecContext_Delete(WebSocketBinaryFrameCodecContext *thiz)
{
    tiny_free(thiz);
}
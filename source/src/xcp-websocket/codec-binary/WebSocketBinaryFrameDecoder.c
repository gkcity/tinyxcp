/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   XcpFrameDecoder.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_log.h>
#include <chacha20poly1305/tiny_chacha20poly1305.h>
#include <tiny_print_binary.h>
#include "WebSocketBinaryFrameDecoder.h"

#define TAG "XcpFrameDecoder"

TINY_LOR
TinyRet WebSocketBinaryFrameDecoder_Decode(WebSocketFrame *frame, int64_t nonce, HKDF *key)
{
    TinyRet ret = TINY_RET_OK;
    int32_t n0 = (int32_t) (nonce & 0xFFFFFFFFL);
    int32_t n1 = (int32_t) (nonce >> 32);
    uint8_t n[8];

    RETURN_VAL_IF_FAIL(frame, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(key, TINY_RET_E_ARG_NULL);

    if (frame->length == 0)
    {
        return ret;
    }

    LOG_D(TAG, "WebSocketBinaryFrameDecoder_Decode: %d bytes", (uint32_t) frame->length);

    n[0] = (uint8_t) (n0);
    n[1] = (uint8_t) (n0 >> 8);
    n[2] = (uint8_t) (n0 >> 16);
    n[3] = (uint8_t) (n0 >> 24);
    n[4] = (uint8_t) (n1);
    n[5] = (uint8_t) (n1 >> 8);
    n[6] = (uint8_t) (n1 >> 16);
    n[7] = (uint8_t) (n1 >> 24);

    ret = tiny_chacha20poly1305_decrypt(key->value,
                                        key->length,
                                        n,
                                        frame->data,
                                        (uint32_t) (frame->length - 16),
                                        frame->data + frame->length - 16,
                                        frame->data,
                                        NULL,
                                        0);
    if (RET_SUCCEEDED(ret))
    {
        frame->length -= 16;
        frame->opcode = OPCODE_TEXT_FRAME;
    }

    return ret;
}
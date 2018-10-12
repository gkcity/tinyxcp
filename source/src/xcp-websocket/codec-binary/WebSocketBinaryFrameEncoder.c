/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   XcpFrameEncoder.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <chacha20poly1305/chacha20poly1305.h>
#include <tiny_log.h>
#include <tiny_malloc.h>
#include "WebSocketBinaryFrameEncoder.h"

#define TAG "XcpFrameEncoder"

TINY_LOR
TinyRet WebSocketBinaryFrameEncoder_Encode(WebSocketFrame *frame, int64_t nonce, HKDF *key)
{
    uint8_t *ciphertext = NULL;
    uint32_t ciphertextLength = (uint32_t) (frame->length + 16);
    int32_t n0 = (int32_t)(nonce & 0xFFFFFFFFL);
    int32_t n1 = (int32_t)(nonce >> 32);
    uint8_t n[8];

    RETURN_VAL_IF_FAIL(frame, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(key, TINY_RET_E_ARG_NULL);

    if (frame->length == 0)
    {
        return TINY_RET_OK;
    }

    LOG_D(TAG, "WebSocketBinaryFrameEncoder_Encode: %d bytes", (uint32_t)frame->length);

    n[0] = (uint8_t)(n0);
    n[1] = (uint8_t)(n0 >> 8);
    n[2] = (uint8_t)(n0 >> 16);
    n[3] = (uint8_t)(n0 >> 24);
    n[4] = (uint8_t)(n1);
    n[5] = (uint8_t)(n1 >> 8);
    n[6] = (uint8_t)(n1 >> 16);
    n[7] = (uint8_t)(n1 >> 24);

    ciphertext = tiny_malloc(ciphertextLength);
    if (ciphertext == NULL)
    {
        return TINY_RET_E_NEW;
    }

    memset(ciphertext, 0, ciphertextLength);

    chacha20poly1305_encrypt(key->value,
                             key->length,
                             n,
                             frame->data,
                             (uint32_t)frame->length,
                             ciphertext,
                             ciphertext + frame->length,
                             NULL,
                             0);

    tiny_free(frame->data);

    frame->opcode = OPCODE_BINARY_FRAME;
    frame->data = ciphertext;
    frame->length = ciphertextLength;

    return TINY_RET_OK;
}
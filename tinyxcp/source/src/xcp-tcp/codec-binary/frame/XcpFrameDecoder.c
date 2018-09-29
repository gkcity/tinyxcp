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
#include <chacha20poly1305/chacha20poly1305.h>
#include <tiny_print_binary.h>
#include "XcpFrameDecoder.h"

#define TAG "XcpFrameDecoder"

TINY_LOR
TinyRet XcpFrameDecoder_Decode(XcpFrame *frame, const uint8_t *data, uint32_t length, int64_t nonce, HKDF *key)
{
    int32_t n0 = (int32_t)(nonce & 0xFFFFFFFFL);
    int32_t n1 = (int32_t)(nonce >> 32);
    uint8_t n[8];

    RETURN_VAL_IF_FAIL(frame, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(data, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(key, TINY_RET_E_ARG_NULL);

    LOG_D(TAG, "FrameDecoder_Decode: %d bytes", length);

    // data = header(2) + frame(N) + signature(16), skip header
    n[0] = (uint8_t)(n0);
    n[1] = (uint8_t)(n0 >> 8);
    n[2] = (uint8_t)(n0 >> 16);
    n[3] = (uint8_t)(n0 >> 24);

    n[4] = (uint8_t)(n1);
    n[5] = (uint8_t)(n1 >> 8);
    n[6] = (uint8_t)(n1 >> 16);
    n[7] = (uint8_t)(n1 >> 24);

//    LOG_BINARY("data", data, length, true);
//    LOG_BINARY("nonce", n, 8, true);
//    LOG_BINARY("key", key->value, key->length, true);
//    LOG_BINARY("frame length", data, 2, true);
//    LOG_BINARY("frame signature", data + length - 16, 16, true);

    memset(frame, 0, sizeof(XcpFrame));
    frame->length = (uint16_t)(length - 2 - 16);

    return chacha20poly1305_decrypt(key->value, key->length, n, data + 2, length - 2 - 16, data + length - 16, frame->data, data, 2);
}
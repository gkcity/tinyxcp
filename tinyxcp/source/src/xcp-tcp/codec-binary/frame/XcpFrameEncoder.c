/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   XcpFrameEncoder.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <chacha20poly1305/chacha20poly1305.h>
#include <tiny_log.h>
#include "XcpFrameEncoder.h"

#define TAG "XcpFrameEncoder"

TINY_LOR
TinyRet XcpFrameEncoder_Encode(XcpFrame *frame, const uint8_t *data, uint32_t length, int64_t nonce, HKDF *key)
{
    uint32_t size = length + XCP_FRAME_SIGNATURE_LENGTH;
    int32_t n0 = (int32_t)(nonce & 0xFFFFFFFFL);
    int32_t n1 = (int32_t)(nonce >> 32);
    uint8_t n[8];

    RETURN_VAL_IF_FAIL(frame, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(data, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(key, TINY_RET_E_ARG_NULL);

    LOG_D(TAG, "FrameEncoder_Encode: %d bytes", length);

    n[0] = (uint8_t)(n0);
    n[1] = (uint8_t)(n0 >> 8);
    n[2] = (uint8_t)(n0 >> 16);
    n[3] = (uint8_t)(n0 >> 24);

    n[4] = (uint8_t)(n1);
    n[5] = (uint8_t)(n1 >> 8);
    n[6] = (uint8_t)(n1 >> 16);
    n[7] = (uint8_t)(n1 >> 24);

    memset(frame, 0, sizeof(XcpFrame));

    frame->data[0] = (uint8_t) (size & 0xFF);
    frame->data[1] = (uint8_t) (size >> 8);
    memcpy(frame->data + 2, data, length);
    frame->length = (uint16_t) (XCP_FRAME_HEADER_LENGTH + length + XCP_FRAME_SIGNATURE_LENGTH);

    chacha20poly1305_encrypt(key->value, key->length, n, data, length, frame->data + 2, frame->data + 2 + length, frame->data, 2);

    return TINY_RET_OK;
}
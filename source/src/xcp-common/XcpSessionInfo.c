/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpSessionInfo.c
 *
 * @remark
 *
 */

#include <tiny_log.h>
#include "XcpSessionInfo.h"

#define TAG "XcpSessionInfo"

void XcpSessionInfo_Create(XcpSessionInfo *info, Curve25519PublicKey *A, Curve25519PublicKey *B)
{
    if (A->length + B->length > XCP_SESSION_INFO_LENGTH)
    {
        LOG_E(TAG, "XcpSessionInfo_Create ERROR");
        return;
    }

    memset(info->value, 0, XCP_SESSION_INFO_LENGTH);
    memcpy(info->value, A->value, A->length);
    memcpy(info->value + A->length, B->value, B->length);
    info->length = A->length + B->length;
}
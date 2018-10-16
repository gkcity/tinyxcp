/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpSessionInfo.h
 *
 * @remark
 *
 */

#ifndef __XCP_SESSION_INFO_H__
#define __XCP_SESSION_INFO_H__

#include <tiny_base.h>
#include <x25519/tiny_curve25519.h>

TINY_BEGIN_DECLS


#define XCP_SESSION_INFO_LENGTH       128

typedef struct _XcpSessionInfo
{
    uint8_t         value[XCP_SESSION_INFO_LENGTH];
    uint32_t        length;
} XcpSessionInfo;

void XcpSessionInfo_Create(XcpSessionInfo *info, Curve25519PublicKey * A, Curve25519PublicKey *B);


TINY_END_DECLS

#endif /* __XCP_SESSION_INFO_H__ */
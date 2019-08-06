/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpClientVerifier.h
 *
 * @remark
 *
 */

#ifndef __XCP_CLIENT_VERIFIER_H__
#define __XCP_CLIENT_VERIFIER_H__

#include <tiny_base.h>
#include <TinyMap.h>
#include <product/Product.h>
#include <ed25519/tiny_ed25519.h>
#include <hkdf/HKDF.h>
#include <handler/XcpMessageHandler.h>
#include "XcpStage.h"
#include "XcpSessionInfo.h"

TINY_BEGIN_DECLS


typedef void(*XcpVerifySuccessHandler) (HKDF *deviceToServerKey, HKDF *serverToDeviceKey, void *ctx);
typedef void(*XcpVerifyFailureHandler) (void *ctx);

typedef TinyRet (*XcpSendQuery) (void *context, XcpMessage *query, XcpMessageHandler handler, void *ctx);

typedef struct _XcpClientVerifier
{
    Product                     * product;
    XcpStage                      stage;
    Curve25519PublicKey           publicKey;
    Curve25519PrivateKey          privateKey;
    Curve25519SharedKey           sharedKey;
    HKDF                          verifyKey;
    ED25519PrivateKey             deviceLTSK;
    ED25519PublicKey              deviceLTPK;
    ED25519PublicKey              serverLTPK;
    XcpSessionInfo                sessionInfo;
    XcpVerifySuccessHandler       onSuccess;
    XcpVerifyFailureHandler       onFailure;
    void                        * ctx;
    XcpSendQuery                  sendQuery;
    int8_t                        binaryCodec;
} XcpClientVerifier;

TINY_LOR
XcpClientVerifier *XcpClientVerifier_New(const char *serverLTPK,
                                         Product *thing,
                                         XcpSendQuery sendQuery,
                                         int8_t binaryCodec);

TINY_LOR
void XcpClientVerifier_Delete(XcpClientVerifier *thiz);

TINY_LOR
void XcpClientVerifier_Start(XcpClientVerifier *thiz,
                             XcpVerifySuccessHandler successHandler,
                             XcpVerifyFailureHandler failureHandler,
                             void *ctx);

TINY_LOR
void XcpClientVerifier_VerifyStart(XcpClientVerifier *thiz);

TINY_LOR
void XcpClientVerifier_VerifyFinish(XcpClientVerifier *thiz);


TINY_END_DECLS

#endif /* __XCP_CLIENT_VERIFIER_H__ */

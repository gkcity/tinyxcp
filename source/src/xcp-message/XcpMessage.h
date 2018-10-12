/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   XcpMessage.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __XCP_MESSAGE_H__
#define __XCP_MESSAGE_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <iq/IQ.h>

TINY_BEGIN_DECLS


typedef struct _XcpMessage
{
    IQ                          iq;
} XcpMessage;

TINY_LOR
XcpMessage * XcpMessage_New(void);

TINY_LOR
void XcpMessage_Delete(XcpMessage *thiz);


TINY_END_DECLS

#endif /* __XCP_MESSAGE_H__  */
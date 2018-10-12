/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   IQError.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "IQErrorFactory.h"

TINY_LOR
XcpMessage * IQError_New(const char *id, int32_t status, const char *description)
{
    XcpMessage * thiz = XcpMessage_New();
    if (thiz != NULL)
    {
        strncpy(thiz->iq.id, id, MESSAGE_ID_LENGTH);
        thiz->iq.type = IQ_TYPE_ERROR;
        thiz->iq.content.error.status = status;
        strncpy(thiz->iq.content.error.description, description, XCP_DESCRIPTION_LENGTH);
    }

    return thiz;
}
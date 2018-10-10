/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   Initialize.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "InitializeFactory.h"

XcpMessage * QueryInitialize_New(const char *id, const char *version, const char *authentication)
{
    XcpMessage *thiz = NULL;

    RETURN_VAL_IF_FAIL(version, NULL);
    RETURN_VAL_IF_FAIL(authentication, NULL);

    do
    {
        thiz = XcpMessage_New();
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(IQ_InitializeQuery(&thiz->iq, id, IQ_METHOD_INITIALIZE)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
            break;
        }

        strncpy(thiz->iq.content.query.content.initialize.version, version, XCP_INITIALIZE_VERSION_LEN);
        strncpy(thiz->iq.content.query.content.initialize.authentication, authentication, XCP_AUTHENTICATION_LEN);
    } while (false);

    return thiz;
}
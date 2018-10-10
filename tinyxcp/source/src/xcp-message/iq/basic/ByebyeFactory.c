/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   ByebyeFactory.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "ByebyeFactory.h"

XcpMessage * QueryByebye_New(const char * id)
{
    XcpMessage *thiz = NULL;

    do
    {
        thiz = XcpMessage_New();
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(IQ_InitializeQuery(&thiz->iq, id, IQ_METHOD_BYEBYE)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

XcpMessage * ResultByebye_New(const char * id)
{
    XcpMessage *thiz = NULL;

    do
    {
        thiz = XcpMessage_New();
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(IQ_InitializeResult(&thiz->iq, id, IQ_METHOD_BYEBYE)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}
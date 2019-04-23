/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpwsServerContext.h
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include "XcpwsServerContext.h"

TINY_LOR
XcpwsServerContext * XcpwsServerContext_New(Thing *thing, HttpRequestHandlers *handlers)
{
    XcpwsServerContext *thiz = tiny_malloc(sizeof(XcpwsServerContext));
    if (thiz != NULL)
    {
        memset(thiz, 0, sizeof(XcpwsServerContext));
        thiz->thing = thing;
        thiz->handlers = handlers;
    }

    return thiz;
}

TINY_LOR
void XcpwsServerContext_Delete(XcpwsServerContext *thiz)
{
    tiny_free(thiz);
}
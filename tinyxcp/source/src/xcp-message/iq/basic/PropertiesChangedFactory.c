/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   PropertiesChangedFactory.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "PropertiesChangedFactory.h"

TINY_LOR
XcpMessage * QueryPropertiesChanged_New(const char *id, PropertyOperations *operations)
{
    XcpMessage * thiz = NULL;

    RETURN_VAL_IF_FAIL(id, NULL);
    RETURN_VAL_IF_FAIL(operations, NULL);

    thiz = XcpMessage_New();
    if (thiz != NULL)
    {
        strncpy(thiz->iq.id, id, MESSAGE_ID_LENGTH);
        thiz->iq.type = IQ_TYPE_QUERY;
        thiz->iq.content.query.method = IQ_METHOD_PROPERTIES_CHANGED;

        if (RET_FAILED(PropertyOperations_Copy(&thiz->iq.content.query.content.propertiesChanged.operations, operations)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
        }
    }

    return thiz;
}
/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   GetPropertiesFactory.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "GetPropertiesFactory.h"

TINY_LOR
XcpMessage * ResultGetProperties_New(const char *id, PropertyOperations *properties)
{
    XcpMessage * thiz = NULL;

    RETURN_VAL_IF_FAIL(properties, NULL);

    thiz = XcpMessage_New();
    if (thiz != NULL)
    {
        strncpy(thiz->iq.id, id, MESSAGE_ID_LENGTH);
        thiz->iq.type = IQ_TYPE_RESULT;
        thiz->iq.content.result.method = IQ_METHOD_GET_PROPERTIES;

        if (RET_FAILED(PropertyOperations_Copy(&thiz->iq.content.result.content.getProperties.properties, properties)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
        }
    }

    return thiz;
}

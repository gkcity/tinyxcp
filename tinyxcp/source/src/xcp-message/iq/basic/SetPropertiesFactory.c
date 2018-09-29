/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "SetPropertiesFactory.h"

TINY_LOR
XcpMessage * ResultSetProperties_New(const char *id, PropertyOperations *properties)
{
    XcpMessage * thiz = NULL;

    RETURN_VAL_IF_FAIL(id, NULL);
    RETURN_VAL_IF_FAIL(properties, NULL);

    thiz = XcpMessage_New();
    if (thiz != NULL)
    {
        strncpy(thiz->iq.id, id, MESSAGE_ID_LENGTH);
        thiz->iq.type = IQ_TYPE_RESULT;
        thiz->iq.content.result.method = IQ_METHOD_SET_PROPERTIES;

        if (RET_FAILED(PropertyOperations_Copy(&thiz->iq.content.result.content.setProperties.properties, properties)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
        }
    }

    return thiz;
}

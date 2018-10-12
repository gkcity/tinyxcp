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
    XcpMessage *thiz = NULL;

    RETURN_VAL_IF_FAIL(properties, NULL);

    do
    {
        thiz = XcpMessage_New();
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(IQ_InitializeResult(&thiz->iq, id, IQ_METHOD_SET_PROPERTIES)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(PropertyOperations_Copy(&thiz->iq.content.result.content.setProperties.properties, properties)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}
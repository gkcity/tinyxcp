/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpwsClientLoopHook.c
 *
 * @remark
 *
 */

#include <product/Product.h>
#include <tiny_log.h>
#include <product/operator/ProductOperator.h>
#include <XcpMessage.h>
#include <iq/basic/PropertiesChangedFactory.h>
#include "XcpwsClientLoopHook.h"
#include <client/XcpwsClient.h>

#define TAG     "XcpwsClientLoopHook"

static void onPropertyChangedResult (XcpMessage *result, void *ctx)
{
    do
    {
        if (result->iq.type == IQ_TYPE_ERROR)
        {
            break;
        }

        if (result->iq.content.result.content.propertiesChanged.operations.properties.size != 1)
        {
            LOG_E(TAG, "RESULT ERROR: PropertyOperation.size != 1");
            break;
        }

        for (uint32_t i = 0; i < result->iq.content.result.content.propertiesChanged.operations.properties.size; ++i)
        {
            PropertyOperation *o = TinyList_GetAt(&result->iq.content.result.content.propertiesChanged.operations.properties, i);
            if (o == NULL)
            {
                LOG_E(TAG, "RESULT ERROR: Get PropertyOperation failed");
                break;
            }

            LOG_I(TAG, "%s.%d.%d status: %d", o->pid.did, o->pid.siid, o->pid.iid, o->status);
        }
    } while (false);
}

void XcpwsClientLoopHook(Channel *thiz, void *ctx)
{
    Product *product = (Product *)thiz;
    PropertyOperations *operations = Product_GetChangedProperties(product);

    LOG_D(TAG, "XcpwsClientLoopHook: %s, TODO: check product properties changed", thiz->id);

    do
    {
        if (operations == NULL)
        {
            break;
        }

        if (operations->properties.size == 0)
        {
            break;
        }

        XcpMessage *query = QueryPropertiesChanged_New("", operations);
        if (query == NULL)
        {
            LOG_D(TAG, "QueryPropertiesChanged_New FAILED!");
            break;
        }

        if (RET_FAILED(XcpwsClient_SendQuery(thiz, query, onPropertyChangedResult, NULL)))
        {
            LOG_D(TAG, "XcpwsClientRuntime_SendQuery FAILED");
            break;
        }

        XcpMessage_Delete(query);
    } while (false);

    if (operations != NULL)
    {
        PropertyOperations_Delete(operations);
    }
}

/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   OnActionInvoke.c
*
* @remark
*
*/

#include "OnActionInvoke.h"
#include "../iid/IID.h"

void OnActionInvoke(ActionOperation *o)
{
    printf("OnActionInvoke: did=[%s], siid = [%d], piid = [%d]\n", o->aid.did, o->aid.siid, o->aid.iid);
    o->status = -100;
}
/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpStage.h
 *
 * @remark
 *
 */

#ifndef __XCP_STAGE_H__
#define __XCP_STAGE_H__

#include <tiny_base.h>

TINY_BEGIN_DECLS


typedef enum _XcpStage
{
    XCP_STAGE_INIT = 0,
    XCP_STAGE_INITIALIZED = 1,
    XCP_STAGE_VERIFY_STARTED = 2,
    XCP_STAGE_VERIFY_FINISHED = 3,
} XcpStage;


TINY_END_DECLS

#endif /* __XCP_STAGE_H__ */
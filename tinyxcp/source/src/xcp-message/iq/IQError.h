/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   IQError.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __IQ_ERROR_H__
#define __IQ_ERROR_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <XcpConstant.h>

TINY_BEGIN_DECLS


typedef struct _IQError
{
    int status;
    char description[XCP_DESCRIPTION_LENGTH];
} IQError;


TINY_END_DECLS

#endif /* __IQ_ERROR_H__  */
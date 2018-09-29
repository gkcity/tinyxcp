/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpFrame.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __XCP_FRAME_H__
#define __XCP_FRAME_H__

#include <tiny_base.h>

TINY_BEGIN_DECLS


#define XCP_FRAME_HEADER_LENGTH             2
#define XCP_FRAME_DATA_MAX_LENGTH           1024
#define XCP_FRAME_SIGNATURE_LENGTH          16
#define XCP_FRAME_MAX_LENGTH                (XCP_FRAME_HEADER_LENGTH + XCP_FRAME_DATA_MAX_LENGTH + XCP_FRAME_SIGNATURE_LENGTH)


typedef struct _XcpFrame
{
    uint8_t     data[XCP_FRAME_MAX_LENGTH];
    uint16_t    length;
} XcpFrame;


TINY_END_DECLS

#endif /* __XCP_FRAME_H__ */
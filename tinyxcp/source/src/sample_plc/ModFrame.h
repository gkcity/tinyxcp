/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   ModFrame.h
*
* @remark
*
*/

#ifndef __ModFrame_H__
#define __ModFrame_H__

#include <tiny_base.h>

TINY_BEGIN_DECLS



typedef struct __attribute__((packed)) _ModFrame
{
    uint16_t  transactionIdentifier;    // For synchronization between messages of server and client
    uint16_t  protocolIdentifier;       // for Modbus/TCP
    uint16_t  length;                   // Number of remaining bytes in this frame
    uint8_t   unitIdentifier;           // 1 Slave address (255 if not used)
    uint8_t   functionCode;             // Function codes as in other variants
    uint8_t   data[1024];               // Data as response or commands
} ModFrame;

typedef enum _ProtocolIdentifier
{
    MODBUS_TCP                          = 0x0000,
    UNI_TE                              = 0x0001,
} ProtocolIdentifier;

typedef enum _FunctionCode
{
    READ_COILS                          = 0x01,
    READ_DISCRETE_INPUTS                = 0x02,
    READ_MULTIPLE_HOLDING_REGISTERS     = 0x03,
    READ_INPUT_REGISTERS                = 0x04,
    WRITE_SINGLE_COIL                   = 0x05,
    WRITE_SINGLE_HOLDING_REGISTER       = 0x06,
    WRITE_MULTIPLE_COILS                = 0x0F,
    WRITE_MULTIPLE_HOLDING_REGISTERS    = 0x10,

    READ_EXCEPTION_STATUS               = 0x14,
    DIAGNOSITIC                         = 0x08,
    GET_COM_EVENT_COUNTER               = 0x0B,
    GET_COM_EVENT_LOG                   = 0x0C,
    REPORT_SLAVE_ID                     = 0x11,
    READ_DEVICE_IDENTIFICATION          = 0x2B,
} FunctionCode;


TINY_END_DECLS

#endif /* __ModFrame_H__ */

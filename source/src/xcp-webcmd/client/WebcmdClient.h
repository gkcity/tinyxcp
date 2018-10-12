/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   WebcmdClient.h
 *
 * @remark
 *
 */

#ifndef __WEBCMD_CLIENT_H__
#define __WEBCMD_CLIENT_H__

#include <tiny_base.h>
#include <XcpConstant.h>
#include <JsonValue.h>

TINY_BEGIN_DECLS


TINY_LOR
bool WebcmdClient_ResetAccessKey(uint16_t port);

TINY_LOR
bool WebcmdClient_GetAccessKey(uint16_t port, char key[XCP_ACCESS_KEY_LEN]);

TINY_LOR
bool WebcmdClient_SendPropertyChanged(uint16_t port, const char *did, uint16_t siid, uint16_t piid, JsonValue *value);

TINY_LOR
bool WebcmdClient_SendEventOccurred(uint16_t port, const char *did, uint16_t siid, uint16_t piid, JsonArray *arguments);


TINY_END_DECLS

#endif /* __WEBCMD_CLIENT_H__ */

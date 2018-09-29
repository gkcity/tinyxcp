/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   FanController.h
*
* @remark
*
*/

#ifndef __FanController_H__
#define __FanController_H__

#include <tiny_base.h>

TINY_BEGIN_DECLS


void fan_set_on(bool on);

bool fan_get_on(void);


TINY_END_DECLS

#endif /* __FanController_H__ */
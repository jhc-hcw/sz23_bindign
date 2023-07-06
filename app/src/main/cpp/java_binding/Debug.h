//
// Created by 靳华财 on 2023/7/6.
//

#ifndef SZ23BINDING_DEBUG_H
#define SZ23BINDING_DEBUG_H

#include <android/log.h>

#ifdef DEBUG_MODE
#define jLogD(fmt, ...) __android_log_print(ANDROID_LOG_INFO,"jhc",fmt,##__VA_ARGS__)
#define jLogStr(_str_) __android_log_print(ANDROID_LOG_INFO,"jhc","jhc:%s",_str_)
#else
#define jLogD(fmt, ...)
#define jLogStr(_str_)
#endif
#endif //SZ23BINDING_DEBUG_H

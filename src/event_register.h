#pragma once

#include "helpers.h"

#define kCGSWorkspaceWillChange 1400
#define kCGSWorkspaceDidChange 1401

#define GLOBAL_CALLBACK(name) void name(uint32_t event_type, void *data, size_t data_length, void *user_data)

// `global_callback` can be used to point to any function that returns void
// and has the same arguments as the function `name`
typedef GLOBAL_CALLBACK (global_callback);

extern int RunApplicationEventLoop (void);
extern CGError SLSRegisterNotifyProc (global_callback *handler, uint32_t event_type, void *user_data);
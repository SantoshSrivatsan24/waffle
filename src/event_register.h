#pragma once

#include <stdlib.h>
#include "helpers.h"
#include "event_handler.h"

typedef enum {

    kCGSWorkspaceWillChange = 1400,
    kCGSWorkspaceDidChange = 1401
} CGSEventType;

#define GLOBAL_CALLBACK(name) void name(CGSEventType type, void *data, size_t data_length, void *user_data)

// global_callback can be used to point to any function that returns void
// and has the same arguments as the function `name`
typedef GLOBAL_CALLBACK (global_callback);

extern CGError SLSRegisterNotifyProc (global_callback *handler, CGSEventType event_type, void *user_data);

GLOBAL_CALLBACK (global_handler);


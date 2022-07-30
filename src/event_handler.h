#pragma once

#include "helpers.h"

#define EVENT_CALLBACK(name) void name ()
typedef EVENT_CALLBACK(event_callback);

EVENT_CALLBACK(EVENT_HANDLER_SPACE_CHANGED);
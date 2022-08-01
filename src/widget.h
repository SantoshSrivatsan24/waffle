#pragma once

#include "helpers.h"
#include "tile_manager.h"

#define kCGSModalWindowTagBit           (1 << 31)
#define kCGSDisableShadowTagBit         (1 <<  3)
#define kCGSHighQualityResamplingTagBit (1 <<  4)
#define kCGSIgnoreForExposeTagBit       (1 <<  7)
#define kCGSOnAllWorkspacesTagBit       (1 << 11)

extern int g_connection;
extern int SLSMainConnectionID(void);
extern CGError SLSDisableUpdate(int cid);
extern CGError SLSReenableUpdate(int cid);
extern CGError SLSNewWindow(int cid, int type, float x, float y, CFTypeRef region, uint32_t *wid);
extern CGError SLSReleaseWindow(int cid, uint32_t wid);
extern CGError SLSSetWindowTags(int cid, uint32_t wid, uint64_t *tags, int tag_size);
extern CGError SLSClearWindowTags(int cid, uint32_t wid, uint64_t *tags, int tag_size);
extern CGError SLSSetWindowShape(int cid, uint32_t wid, float x_offset, float y_offset, CFTypeRef shape);
extern CGError SLSSetWindowResolution(int cid, uint32_t wid, double res);
extern CGError SLSSetWindowOpacity(int cid, uint32_t wid, bool isOpaque);
extern CGError SLSOrderWindow(int cid, uint32_t wid, int mode, uint32_t relativeToWID);
extern CGError SLSSetWindowLevel(int cid, uint32_t wid, int level);
extern CGError SLSRemoveAllTrackingAreas(uint32_t cid, uint32_t wid);
extern CGContextRef SLWindowContextCreate(int cid, uint32_t wid, CFDictionaryRef options);
extern CGError CGSNewRegionWithRect(CGRect *rect, CFTypeRef *outRegion);

typedef struct {

    uint32_t id;
    CGContextRef context;
    CGRect frame;
    tile_manager_t *tile_manager;
} widget_t;

void *widget_create ();
void widget_init (widget_t *widget, CGRect frame);
void widget_render (widget_t *widget);
void widget_refresh (widget_t *widget);
void widget_close (widget_t *widget);
void widget_destroy (widget_t *widget);

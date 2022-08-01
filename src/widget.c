#include "widget.h"

void *widget_create () {

    widget_t *widget = (widget_t *) malloc (sizeof(widget_t));
    memset (widget, 0, sizeof(widget_t));
    widget->tile_manager = tile_manager_create ();
    return widget;
}

void widget_init (widget_t *widget, CGRect frame) {

    uint64_t set_tags = kCGSHighQualityResamplingTagBit | kCGSOnAllWorkspacesTagBit;
    CFTypeRef region;
    CGSNewRegionWithRect(&frame, &region);

    /// The real widget top/left is the sum of the region's top/left and the top/left parameters.
    SLSNewWindow (g_connection, 2, 0, 0, region, &widget->id);
    SLSSetWindowResolution (g_connection, widget->id, 2.0f);
    SLSSetWindowTags (g_connection, widget->id, &set_tags, 64);
    SLSSetWindowOpacity (g_connection, widget->id, 0);
    SLSSetWindowLevel (g_connection, widget->id, kCGDesktopWindowLevel);

    widget->context = SLWindowContextCreate(g_connection, widget->id, 0);
    widget->frame = (CGRect) {{0, 0}, frame.size};
}

void widget_render (widget_t *widget) {

    printf ("Widget rendering...\n");

    SLSDisableUpdate (g_connection);
    SLSOrderWindow (g_connection, widget->id, -1, 0);
    CGContextClearRect (widget->context, widget->frame);

    tile_manager_render_tiles (widget->tile_manager, widget->context);

    CGContextFlush (widget->context);
    SLSOrderWindow (g_connection, widget->id, 1, 0);
    SLSReenableUpdate (g_connection);
}

void widget_refresh (widget_t *widget) {

    // widget_close (widget);
    widget_render (widget);
}

void widget_close (widget_t *widget) {

    CGContextRelease (widget->context);
    SLSReleaseWindow (g_connection, widget->id);
}

void widget_destroy (widget_t *widget) {

    widget_close (widget);
    free (widget);
}
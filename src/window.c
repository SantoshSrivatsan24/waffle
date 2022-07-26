#include "window.h"

void window_init (window_t *window, CGRect frame) {

    CFTypeRef region;
    CGSNewRegionWithRect(&frame, &region);

    /// The real window top/left is the sum of the region's top/left and the top/left parameters.
    SLSNewWindow(g_connection, 2, 0, 0, region, &window->id);
    SLSSetWindowResolution(g_connection, window->id, 2.0f);
    SLSSetWindowOpacity(g_connection, window->id, 0);
    // SLSSetWindowLevel(g_connection, window->id, CGWindowLevelForKey(3));

    window->context = SLWindowContextCreate(g_connection, window->id, 0);
    window->frame = frame;
    window->render_frame = (CGRect) {{0, 0}, frame.size};
}
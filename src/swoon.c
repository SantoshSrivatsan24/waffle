#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helpers.h"
#include "window.h"
#include "tile.h"

int g_connection;

int main(int argc, char **argv) {

    g_connection = SLSMainConnectionID();

    CGDirectDisplayID did = CGMainDisplayID();
    CGRect display = CGDisplayBounds(did);
    CGRect window_frame = CGRectInset(display, 300, 200);
    CGRect tile_frame = (CGRect) {{10, 10}, {100, 200}};

    window_t *window = malloc (sizeof(window_t));
    memset(window, 0, sizeof(window_t));

    tile_t *tile = malloc (sizeof(tile_t));
    memset(tile, 0, sizeof(tile_t));

    window_init(window, window_frame);
    tile_init(tile, tile_frame, 0xaf282c34, 0xaf56b6c2, 2, 10);

    for (;;) {
        SLSDisableUpdate(g_connection);
        SLSOrderWindow(g_connection, window->id, -1, 0);
        CGContextClearRect(window->context, window->render_frame);

        tile_render(window, tile);

        CGContextFlush(window->context);
        SLSOrderWindow(g_connection, window->id, 1, 0);
        SLSReenableUpdate(g_connection);

        sleep(1);
    }

    return 0;
}
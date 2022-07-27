#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helpers.h"
#include "window.h"
#include "tile_manager.h"
#include "tile.h"

int g_connection;

int main(int argc, char **argv) {

    g_connection = SLSMainConnectionID();

    CGDirectDisplayID did = CGMainDisplayID();
    CGRect display = CGDisplayBounds(did);
    CGRect window_frame = CGRectInset(display, 300, 200);

    window_t *window = malloc (sizeof(window_t));
    memset(window, 0, sizeof(window_t));

    window_init(window, window_frame);

    tile_manager_t *tile_manager = tile_manager_create();

    CGSize tile1_size = {150, 250};
    CGSize tile2_size = {250, 300};
    CGSize tile3_size = {100, 100};
    CGSize tile4_size = {150, 400};
    tile_manager_create_tile (tile_manager, tile1_size, 0xaf282c34, 0xaf56b6c2, 4, 10);
    tile_manager_create_tile (tile_manager, tile2_size, 0xaf282c34, 0xaf56b6c2, 4, 10);
    tile_manager_create_tile (tile_manager, tile3_size, 0xaf282c34, 0xaf56b6c2, 4, 10);
    tile_manager_create_tile (tile_manager, tile4_size, 0xaf282c34, 0xaf56b6c2, 4, 10);
    tile_manager_compute_positions (window->render_frame, tile_manager);

    for (;;) {
        SLSDisableUpdate(g_connection);
        SLSOrderWindow(g_connection, window->id, -1, 0);
        CGContextClearRect(window->context, window->render_frame);

        tile_manager_render_tiles (window->context, tile_manager);

        CGContextFlush(window->context);
        SLSOrderWindow(g_connection, window->id, 1, 0);
        SLSReenableUpdate(g_connection);

        sleep(1);
    }

    return EXIT_SUCCESS;
}
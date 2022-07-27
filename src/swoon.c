#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helpers.h"
#include "window.h"
#include "tile_manager.h"
#include "tile.h"

#define BACKGROUND  0xaf282c34
#define RED         0xafe06c75
#define GREEN       0xaf98c370
#define YELLOW      0xafe5c07b
#define BLUE        0xaf61afef
#define VIOLET      0xafc678dd
#define TURQUOISE   0xaf56b6c2
#define GREY        0xafabb2bf

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

    position_t tpos0 = {POSITION_LEFT, 0};
    int tid0  = tile_manager_create_tile (tile_manager, tile1_size, tpos0, BACKGROUND, RED, 4, 10);

    position_t tpos1 = {POSITION_RIGHT, tid0};
    int tid1 = tile_manager_create_tile (tile_manager, tile2_size, tpos1, BACKGROUND, GREEN, 4, 10);

    position_t tpos2 = {POSITION_BELOW, tid0};
    int tid2 = tile_manager_create_tile (tile_manager, tile3_size, tpos2, BACKGROUND, YELLOW, 4, 10);

    position_t tpos3 = {POSITION_RIGHT, tid1};
    int tid3 = tile_manager_create_tile (tile_manager, tile4_size, tpos3, BACKGROUND, BLUE, 4, 10);

    tile_manager_order_tiles (tile_manager, window->render_frame);

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
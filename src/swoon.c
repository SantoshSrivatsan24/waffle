#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helpers.h"
#include "window.h"
#include "tile_manager.h"
#include "tile.h"
#include "event_register.h"
#include "event_handler.h"
#include "event_loop.h"

#define BACKGROUND  0xff282c34
#define RED         0xffe06c75
#define GREEN       0xff98c370
#define YELLOW      0xffe5c07b
#define BLUE        0xff61afef
#define VIOLET      0xffc678dd
#define TURQUOISE   0xff56b6c2
#define GREY        0xffabb2bf

int g_connection;
extern int RunApplicationEventLoop (void);

int main(int argc, char **argv) {

    g_connection = SLSMainConnectionID();

    CGDirectDisplayID did = CGMainDisplayID();
    CGRect display = CGDisplayBounds(did);
    CGRect window_frame = CGRectInset(display, 300, 200);

    window_t *window = malloc (sizeof(window_t));
    memset(window, 0, sizeof(window_t));

    window_init(window, window_frame);

    tile_manager_t *tile_manager = tile_manager_create();

    CGSize tsize0 = {200, 300};
    CGSize tsize1 = {100, 150};
    CGSize tsize2 = {100, 150};
    CGSize tsize3 = {100, 150};
    CGSize tsize4 = {100, 150};
    CGSize tsize5 = {100, 300};
    CGSize tsize6 = {300, 100};
    CGSize tsize7 = {200, 100};

    position_t tpos0 = {POSITION_LEFT, 0};
    int tid0  = tile_manager_create_tile (tile_manager, tsize0, tpos0, BACKGROUND, TURQUOISE, 5, 0, 10);

    // tile 1 is positioned to the right of tile 0
    position_t tpos1 = {POSITION_RIGHT, tid0};
    int tid1 = tile_manager_create_tile (tile_manager, tsize1, tpos1, BACKGROUND, RED, 5, 0, 10);

    position_t tpos2 = {POSITION_RIGHT, tid1};
    int tid2 = tile_manager_create_tile (tile_manager, tsize2, tpos2, BACKGROUND, GREEN, 5, 0, 10);

    // tile 3 is positioned below tile 1
    position_t tpos3 = {POSITION_BELOW, tid1};
    int tid3 = tile_manager_create_tile (tile_manager, tsize3, tpos3, BACKGROUND, BLUE, 5, 0, 10);

    position_t tpos4 = {POSITION_RIGHT, tid3};
    int tid4 = tile_manager_create_tile (tile_manager, tsize4, tpos4, BACKGROUND, VIOLET, 5, 0, 10);

    position_t tpos5 = {POSITION_RIGHT, tid2};
    int tid5 = tile_manager_create_tile (tile_manager, tsize5, tpos5, BACKGROUND, TURQUOISE, 5, 0, 10);

    position_t tpos6 = {POSITION_BELOW, tid0};
    int tid6 = tile_manager_create_tile (tile_manager, tsize6, tpos6, BACKGROUND, TURQUOISE, 5, 0, 10);

    position_t tpos7 = {POSITION_RIGHT, tid6};
    int tid7 = tile_manager_create_tile (tile_manager, tsize7, tpos7, BACKGROUND, TURQUOISE, 3, 0, 10);

    tile_manager_order_tiles (tile_manager, window->frame);
    tile_manager_center_tiles (tile_manager, window->frame);


    SLSDisableUpdate(g_connection);
    SLSOrderWindow(g_connection, window->id, -1, 0);
    CGContextClearRect(window->context, window->frame);

    tile_manager_render_tiles (window->context, tile_manager);

    CGContextFlush(window->context);
    SLSOrderWindow(g_connection, window->id, 1, 0);
    SLSReenableUpdate(g_connection);

    event_loop_t event_loop;
    event_loop_begin (&event_loop);

    // Execute the function `global_handler` when the workspace changes
    // `global_handler` starts the event handler for the individual events in a separate thread
    // If we weren't using another thread to handle events, then we could pass the individual event handler
    // to SLSRegisterNotifyProc
    SLSRegisterNotifyProc (global_handler, kCGSWorkspaceDidChange, NULL);
       
    RunApplicationEventLoop();

    return EXIT_SUCCESS;
}
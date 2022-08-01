#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "helpers.h"
#include "widget.h"
#include "tile_manager.h"
#include "tile.h"
#include "event_register.h"
#include "event_handler.h"
#include "event_loop.h"
#include "socket.h"

#define SOCK_PATH "waffle.socket"

#define BACKGROUND  0xff282c34
#define RED         0xffe06c75
#define GREEN       0xff98c370
#define YELLOW      0xffe5c07b
#define BLUE        0xff61afef
#define VIOLET      0xffc678dd
#define TURQUOISE   0xff56b6c2
#define GREY        0xffabb2bf

int g_connection;

widget_t *widget;
event_loop_t g_event_loop;
daemon_t g_daemon;

static void sigint_handler (int sig) {

    printf ("waffle: interrupt.\n");
    unlink (SOCK_PATH);
    exit (EXIT_SUCCESS);
}

static GLOBAL_CALLBACK (global_handler) {

    // The arguments that the event handler needs are pushed onto a queue
    // TODO: implement memory pool and queue
    event_loop_signal (&g_event_loop);
}

static void parse_arguments (int argc, char *argv[]) {

    int sockfd;

    if (!socket_daemon_connect(&sockfd, SOCK_PATH)) {
        perror ("waffle: failed to open socket.");
    }

    int message_len = 0;
    int argl[argc];

    for (int i = 1; i < argc; i++) {

        argl[i] = strlen (argv[i]);
        message_len += argl[i];
    }

    char message[message_len];
    char *temp = message;

    // String together all of the command line arguments
    for (int i = 1; i < argc; i++) {

        memcpy (temp, argv[i], argl[i]);
        temp += argl[i];
        *temp++ = '\0';
    }
    *temp++ = '\0';

    printf("num args: %d\n", argc);
    printf("message length: %d\n", message_len);
    printf ("%s\n", message);

    socket_daemon_write (sockfd, message);
    socket_close (sockfd);

    exit (EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {

    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sa.sa_flags = 0;
    sigemptyset (&sa.sa_mask);

    if (sigaction (SIGINT, &sa, NULL) == -1) {
        perror ("waffle: sigaction\n");
        exit (EXIT_FAILURE);
    }


    if (argc > 1) parse_arguments (argc, argv);

    g_connection = SLSMainConnectionID();

    CGDirectDisplayID did = CGMainDisplayID();
    CGRect display = CGDisplayBounds(did);
    CGRect widget_frame = CGRectInset(display, 300, 200);

    widget = widget_create ();
    widget_init(widget, widget_frame);

    CGSize tsize0 = {200, 300};
    CGSize tsize1 = {100, 150};
    CGSize tsize2 = {100, 150};
    CGSize tsize3 = {100, 150};
    CGSize tsize4 = {100, 150};
    CGSize tsize5 = {100, 300};
    CGSize tsize6 = {300, 100};
    CGSize tsize7 = {200, 100};

    position_t tpos0 = {POSITION_LEFT, 0};
    int tid0  = tile_manager_create_tile (widget->tile_manager, tsize0, tpos0, BACKGROUND, TURQUOISE, 5, 0, 10);

    // tile 1 is positioned to the right of tile 0
    position_t tpos1 = {POSITION_RIGHT, tid0};
    int tid1 = tile_manager_create_tile (widget->tile_manager, tsize1, tpos1, BACKGROUND, RED, 5, 0, 10);

    position_t tpos2 = {POSITION_RIGHT, tid1};
    int tid2 = tile_manager_create_tile (widget->tile_manager, tsize2, tpos2, BACKGROUND, GREEN, 5, 0, 10);

    // tile 3 is positioned below tile 1
    position_t tpos3 = {POSITION_BELOW, tid1};
    int tid3 = tile_manager_create_tile (widget->tile_manager, tsize3, tpos3, BACKGROUND, BLUE, 5, 0, 10);

    position_t tpos4 = {POSITION_RIGHT, tid3};
    int tid4 = tile_manager_create_tile (widget->tile_manager, tsize4, tpos4, BACKGROUND, VIOLET, 5, 0, 10);

    position_t tpos5 = {POSITION_RIGHT, tid2};
    int tid5 = tile_manager_create_tile (widget->tile_manager, tsize5, tpos5, BACKGROUND, TURQUOISE, 5, 0, 10);

    position_t tpos6 = {POSITION_BELOW, tid0};
    int tid6 = tile_manager_create_tile (widget->tile_manager, tsize6, tpos6, BACKGROUND, TURQUOISE, 5, 0, 10);

    position_t tpos7 = {POSITION_RIGHT, tid6};
    int tid7 = tile_manager_create_tile (widget->tile_manager, tsize7, tpos7, BACKGROUND, TURQUOISE, 3, 0, 10);

    tile_manager_order_tiles (widget->tile_manager, widget->frame);
    tile_manager_center_tiles (widget->tile_manager, widget->frame);

    widget_render (widget);

    event_loop_begin (&g_event_loop);
    if (!socket_daemon_begin (&g_daemon, SOCK_PATH)) {
        perror ("waffle: error creating daemon.\n");
        exit (EXIT_FAILURE);
    }

    // Execute the function `global_handler` when the workspace changes
    // `global_handler` starts the event handler for the individual events in a separate thread
    // If we weren't using another thread to handle events, then we could pass the individual event handler
    // to SLSRegisterNotifyProc
    SLSRegisterNotifyProc (global_handler, kCGSWorkspaceDidChange, NULL);
       
    RunApplicationEventLoop();

    return EXIT_SUCCESS;
}
#include "socket.h"

static void socket_close (int sockfd) {
    shutdown (sockfd, SHUT_RDWR);
    close (sockfd);
}

static void *socket_connection_handler (void *args) {

    daemon_t *daemon = (daemon_t *) args;

    while (daemon->is_running) {

        printf ("waffle: socket daemon running...\n");

        int sockfd = accept (daemon->sockfd, NULL, 0);
        char message[50];
        int n = read (sockfd, message, 50);
        if (n) {
            printf ("%.*s\n", n, message);
        } else {
            socket_close (sockfd);
        }
    }
    pthread_exit (EXIT_SUCCESS);
}

bool socket_daemon_begin (daemon_t *daemon, char *sock_path) {

    if ((daemon->sockfd = socket (AF_UNIX, SOCK_STREAM, 0)) == -1) {
        return false;
    }

    struct sockaddr_un sockaddr;
    sockaddr.sun_family = AF_UNIX;
    strcpy (sockaddr.sun_path, sock_path);

    if ((bind (daemon->sockfd, (struct sockaddr *)&sockaddr, sizeof (sockaddr))) == -1) {
        return false;
    }

    if ((listen (daemon->sockfd, SOMAXCONN)) == -1) {
        return false;
    }

    daemon->is_running = true;
    pthread_create (&daemon->thread, NULL, socket_connection_handler, daemon);

    return true;
}

bool socket_daemon_connect (int *sockfd, char *sock_path) {

    if ((*sockfd = socket (AF_UNIX, SOCK_STREAM, 0)) == -1) {
        return false;
    }

    struct sockaddr_un sockaddr;
    sockaddr.sun_family = AF_UNIX;
    strcpy (sockaddr.sun_path, sock_path);

    return connect (*sockfd, (struct sockaddr *)&sockaddr, sizeof (sockaddr)) != -1;
}

bool socket_daemon_write (int sockfd, char *message) {

    return write (sockfd, message, strlen(message));
}
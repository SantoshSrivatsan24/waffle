#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

typedef struct {

    int sockfd;
    pthread_t thread;
    bool is_running;
} daemon_t;

bool socket_daemon_begin (daemon_t *daemon, char *sock_path);
bool socket_daemon_connect (int *sockfd, char *sock_path);
bool socket_daemon_write (int sockfd, char *message);
void socket_close (int sockfd);

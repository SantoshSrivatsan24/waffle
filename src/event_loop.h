#pragma once

#include "helpers.h"
#include <pthread.h>
#include <semaphore.h>

sem_t *smore;

typedef struct {
    
    pthread_t thread;
    sem_t *smore; // s'mores hehe (semaphore)
    bool is_running;
} event_loop_t;

bool event_loop_begin (event_loop_t *event_loop);
void event_loop_signal (event_loop_t *event_loop);

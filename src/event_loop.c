// The event loop takes care of events that come into the application

#include "event_loop.h"
#include "event_handler.h"

static void *event_loop_run (void *args) {

    event_loop_t *event_loop = (event_loop_t *) args;

    while (event_loop->is_running) {
        
        sem_wait (event_loop->smore);

        // Do something after event has happened
        // But how on earth do I detect an event????

        // TODO: Write a simple program that detects a mouse click using InstallEventHandler
        EVENT_HANDLER_SPACE_CHANGED();

    }
    
    sem_close (smore);
    pthread_exit (NULL);
}

bool event_loop_begin (event_loop_t *event_loop) {

    if (event_loop->is_running) return false;

    event_loop->is_running = true;
    event_loop->smore = sem_open ("smore", O_CREAT, 0600, 0);
    sem_unlink ("smore");
    pthread_create (&event_loop->thread, NULL, &event_loop_run, event_loop);

    return true;
}

void event_loop_signal (event_loop_t *event_loop) {

    sem_post (event_loop->smore);
}



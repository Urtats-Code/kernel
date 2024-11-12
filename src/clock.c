// Libraries

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Configuration files

#include "../config/clock_globals.h"
#include "../config/timer_globals.h"


// Initialize extern variables

pthread_mutex_t clock_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t timer_cond = PTHREAD_COND_INITIALIZER; 
pthread_cond_t free_timer_tick = PTHREAD_COND_INITIALIZER; 


int done_timers = 0;

void *create_clock(void *args) {

    struct Clock *defined_clock = (struct Clock *) args;

    if (defined_clock == NULL) {
        printf("Error: defined_clock is NULL\n");
        return NULL;
    }

    int tick_interval_microseconds = 1000000 / defined_clock->simulating_hz;
    int tick_counter = 0;

    printf("Clock ID %d created. Running at %d Hz.\n", defined_clock->id, defined_clock->simulating_hz);

    pthread_mutex_lock(&clock_mutex);

    while (1) { 

        usleep(tick_interval_microseconds);

        // Wait until all timers have completed their ticks
        while (done_timers < TIMER_NUM) {
            pthread_cond_wait(&timer_cond, &clock_mutex);
        }

        done_timers = 0;
        pthread_cond_broadcast(&free_timer_tick);

        printf("Clock ID %d tick %d.\n", defined_clock->id, ++tick_counter);

    }

    pthread_mutex_unlock(&clock_mutex); 

    return NULL;
}

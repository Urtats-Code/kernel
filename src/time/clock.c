// Libraries

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Configuration files

#include "../../config/clock_globals.h"
#include "../../config/timer_globals.h"
#include "../../config/signal_globals.h"


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

    if( SHOW_CLOCK_CONFIG ){

        printf("==============================================\n");
        printf("|            Clock Information               |\n");
        printf("==============================================\n");

        printf("| %-20s | %10d |\n", "Clock ID", defined_clock -> id );
        printf("| %-20s | %10d Hz |\n", "Frequency", defined_clock -> simulating_hz );

        printf("==============================================\n");
        
    }


    pthread_mutex_lock(&clock_mutex);

    while ( program_executing ) { 

        usleep(tick_interval_microseconds);

        // Wait until all timers have completed their ticks
        while (done_timers < TIMER_NUM) {
            pthread_cond_wait(&timer_cond, &clock_mutex);
        }

        done_timers = 0;
        pthread_cond_broadcast(&free_timer_tick);

    }

    pthread_mutex_unlock(&clock_mutex); 

    return NULL;
}

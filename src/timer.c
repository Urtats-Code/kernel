// Libraries

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Configuration files

#include "../config/timer_globals.h"
#include "../config/clock_globals.h"

void *create_timer(void *args) {

    struct Timer *defined_timer = (struct Timer *) args;
    
    int second_counter = 0;
    int tick_counter = 0;

    pthread_mutex_lock(&clock_mutex);

    while (1) {
        
        done_timers += 1;
        tick_counter++;

        if ((tick_counter % defined_timer->clock_hz) == 0) {
            second_counter++;
        }

        if( second_counter == defined_timer -> signal_time ){
            printf("Timer %d has sent a signal at %d seconds \n", defined_timer -> id, second_counter );
            second_counter = 0;
        }


        pthread_cond_signal(&timer_cond);  
        pthread_cond_wait(&free_timer_tick, &clock_mutex);

    }

    pthread_mutex_unlock(&clock_mutex);  // Unlock once the timer exits the loop
    return NULL;
}


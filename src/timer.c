// Libraries

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Configuration files

#include "../config/timer_globals.h"
#include "../config/clock_globals.h"
#include "../config/process_globals.h"
#include "../config/signal_globals.h"
#include "../config/scheduler_globlas.h"



void *create_timer(void *args) {

    struct Timer *defined_timer = (struct Timer *) args;
    
    // printf("A timer was created that send signals every %d seconds \n", defined_timer->signal_time );

    int second_counter = 0;
    int tick_counter = 0;

    pthread_mutex_lock(&clock_mutex);

    while ( program_executing ) {
        
        done_timers += 1;
        tick_counter++;

        if ((tick_counter % defined_timer->clock_hz) == 0) {
            second_counter++;
        }

        if( second_counter == defined_timer -> signal_time ){
    
            if( SHOW_WHEN_PROCESS_IS_CREATED ){
                printf("A process was created: \n");
            }
            
            create_process();

            second_counter = 0;
        }


        pthread_cond_signal(&timer_cond);  
        pthread_cond_wait(&free_timer_tick, &clock_mutex);

    }

    pthread_mutex_unlock(&clock_mutex);  // Unlock once the timer exits the loop
    return NULL;
}







void *create_scheduler_timer(void *args) {

    struct Timer *defined_timer = (struct Timer *) args;
    
    // printf("A timer was created that send signals every %d seconds \n", defined_timer->signal_time );

    int second_counter = 0;
    int tick_counter = 0;

    pthread_mutex_lock(&clock_mutex);

    while ( program_executing ) {
        
        done_timers += 1;
        tick_counter++;

        if ((tick_counter % defined_timer->clock_hz) == 0) {
            second_counter++;
        }

        if( second_counter == defined_timer -> signal_time ){

            if( SHOW_WHEN_TIMER_SCHEDULES ){
                printf("Scheduling happened: \n");
            }

            schedule_process(); 
            second_counter = 0;
        }


        pthread_cond_signal(&timer_cond);  
        pthread_cond_wait(&free_timer_tick, &clock_mutex);

    }

    pthread_mutex_unlock(&clock_mutex);  // Unlock once the timer exits the loop
    return NULL;
}


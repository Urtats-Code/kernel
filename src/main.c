// Libraries

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Configuration files

#include "../config/clock_globals.h"
#include "../config/timer_globals.h"

// Global variables

pthread_t clock_thread;

int main(void) {

    pthread_t clock_thread;
    pthread_t timers[TIMER_NUM];
    
    struct Clock main_clock = {1, 10};

    
    if (pthread_create(&clock_thread, NULL, create_clock, (void *)&main_clock) != 0) {
        perror("Failed to create clock thread");
        return 1;
    }

    printf("Clock thread started. I am doing other things. \n");
    
    for (int i = 0; i < TIMER_NUM; i++) {
        
        struct Timer new_timer = { i, main_clock.simulating_hz, 2 };
        
        if (pthread_create(&timers[i], NULL, create_timer, (void *) &new_timer ) != 0) {
            perror("Failed to create timer thread");
            return 1;
        }

        printf("Timer thread %d started.\n",  new_timer.id );

    }
    
    sleep(15);

    for (int i = 0; i < TIMER_NUM; i++) {
        pthread_cancel(timers[i]); 
        pthread_join(timers[i], NULL); 
    }

    pthread_cancel(clock_thread);
    pthread_join(clock_thread, NULL);

    printf("Main program is exiting.\n");
    return 0;
}

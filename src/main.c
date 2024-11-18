// Libraries

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Configuration files

#include "../config/clock_globals.h"
#include "../config/timer_globals.h"
#include "../config/process_globals.h"
#include "../config/signal_globals.h"

// Global variables

pthread_t clock_thread;
pthread_t timers[TIMER_NUM];
volatile sig_atomic_t terminate_flag = 0; 
int program_executing = 1;

int main(void) {
    initialize_signal_handler();
    
    struct Clock main_clock = {1, 10};

    
    if (pthread_create(&clock_thread, NULL, create_clock, (void *)&main_clock) != 0) {
        perror("Failed to create clock thread");
        return 1;
    }

    printf("Clock thread started. I am doing other things. \n");
    
    for (int i = 0; i < TIMER_NUM; i++) {
        
        int duration_seconds = 1;
        
        struct Timer new_timer = { i, main_clock.simulating_hz, duration_seconds };
        
        if (pthread_create(&timers[i], NULL, create_timer, (void *) &new_timer ) != 0) {
            perror("Failed to create timer thread");
             cleanup_and_exit(0);
            return 1;
        }

    }

     while (!terminate_flag) {
        sleep(1);
    }


    printf("Main program is exiting.\n");

    return 0;
}



void cleanup_and_exit( int signum ){


    program_executing = 0;

    printf("Canceling and joining all TIMER threads. \n");

    for (int i = 0; i < TIMER_NUM; i++) {
        pthread_cancel(timers[i]);
        pthread_join(timers[i], NULL);
    }

    printf("Canceling and joining CLOCK thread. \n");

    pthread_cancel(clock_thread);
    pthread_join(clock_thread, NULL);

    printf("Freeing alocated memory. \n");

    free_all_pcbs();

    printf("Cleaned up resources. Exiting program.\n");
    exit(signum); 

}

void initialize_signal_handler( void ) {

    struct sigaction sa;
    sa.sa_handler = cleanup_and_exit; 
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) { // Handle Ctrl+C
        perror("Failed to set SIGINT handler");
        exit(1);
    }

    if (sigaction(SIGTERM, &sa, NULL) == -1) { // Handle termination signal
        perror("Failed to set SIGTERM handler");
        exit(1);
    }

}

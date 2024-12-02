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
#include "../config/pc_globals.h"

// Global variables

pthread_t clock_thread;
pthread_t timers[TIMER_NUM];
volatile sig_atomic_t terminate_flag = 0; 
int program_executing = 1;
struct PC pc; 

int main(void) {
    initialize_signal_handler();

    pc = initialize_pc(); 


    struct Clock main_clock = {1, 10};

    
    if (pthread_create(&clock_thread, NULL, create_clock, (void *)&main_clock) != 0) {
        perror("Failed to create clock thread");
        return 1;
    }

    printf("Clock thread started. I am doing other things. \n");
    
    for (int i = 0; i < TIMER_NUM; i++) {

        int duration_seconds = i + 1;

        struct Timer *new_timer = malloc(sizeof(struct Timer));
        if (new_timer == NULL) {
            perror("Failed to allocate memory for Timer");
            cleanup_and_exit(0);
            return 1;
        }
        
        new_timer->id = i;
        new_timer->clock_hz = main_clock.simulating_hz;
        new_timer->signal_time = duration_seconds;

        if( new_timer -> signal_time == 1 ){

            if (pthread_create(&timers[i], NULL, create_scheduler_timer, (void *) new_timer) != 0) {
                perror("Failed to create timer thread");
                free(new_timer); 
                cleanup_and_exit(0);
                return 1;
            }

        } else {


            if (pthread_create(&timers[i], NULL, create_timer, (void *) new_timer) != 0) {
                perror("Failed to create timer thread");
                free(new_timer); 
                cleanup_and_exit(0);
                return 1;
            }


        }


    }
    

    if( SHOW_PC_CONFIG ){

        printf("-------------- \n");
        printf("PC Configuration \n");
        print_pc( &pc );
        printf("-------------- \n");
        
    }


    while (!terminate_flag) {}

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

    printf("Freeing alocated PCB memory. \n");

    free_all_pcbs();

    printf("Freeing alocated PC memory. \n");

    free_pc_memory( &pc );    

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

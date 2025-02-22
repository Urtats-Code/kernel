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
#include "../config/memory_globals.h"
#include "../config/global_config.h"

// Global variables

pthread_t loader_thread;
pthread_t clock_thread;
pthread_t timers[TIMER_NUM];
volatile sig_atomic_t terminate_flag = 0; 
int program_executing = 1;
struct PC pc; 

int main(void) {
    
    initialize_signal_handler();
    physical_virtual_memory_mapping_calculations();

    

    pc = initialize_pc(); 


    struct Clock main_clock = {1, CLOCK_HZ};



    char *file_name = "some_value.txt";  



    if (pthread_create(&clock_thread, NULL, create_clock, (void *)&main_clock) != 0) {
        perror("Failed to create clock thread");
        return 1;
    }

    if (pthread_create(&loader_thread, NULL, create_load_process, (void *)file_name) != 0) {
        perror("Failed to create loader thread");
        return 1;
    }
    
    int duration_seconds = 1;
    
    for (int i = 0; i < TIMER_NUM; i++) {


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

            duration_seconds = i + 2;

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
    pthread_join(loader_thread, NULL);

    printf("Freeing alocated PCB memory. \n");

    free_all_pcbs();

    printf("Freeing alocated PC memory. \n");

    free_pc_memory( &pc );    

    printf("Freeing alocated simulated Virtual / Physical memory . \n");

    free_physical_virtual_memory();

    

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


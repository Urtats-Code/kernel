// Libraries

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Configuration files

#include "../config/clock_globals.h"

// Global variables

pthread_t clock_thread;

int main( void ){

    struct Clock myClock = {1, 10}; 
    

    if (pthread_create(&clock_thread, NULL, create_clock, (void *) &myClock) != 0) {
        perror("Failed to create clock thread");
        return 1;
    }

    printf("I am doing other things. \n");

    sleep(5);

    printf("Main program is exiting.\n");
    return 0;

}


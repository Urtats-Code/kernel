// Libraries

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Configuration files

#include "../config/clock_globals.h"


void *create_clock( void *args ){

    struct Clock *defined_clock = (struct Clock *) args;

    if (defined_clock == NULL) {
        printf("Error: defined_clock is NULL\n");
        return NULL;
    }

    int tick_interval_microseconds = 1000000 / defined_clock->simulating_hz;
    int tick_counter = 0; 
    int second_counter = 0; 


    printf("Clock ID %d created. Running at %d Hz.\n", defined_clock->id, defined_clock->simulating_hz);

    while (1) { 

        printf("Clock ID %d tick %d.\n", defined_clock->id, ++tick_counter);

        if (tick_counter % defined_clock->simulating_hz == 0) {
            second_counter++; 
            printf("Clock ID %d has been running for %d seconds.\n", defined_clock->id, second_counter);
        }

        usleep(tick_interval_microseconds);
    }


    return NULL; 
}


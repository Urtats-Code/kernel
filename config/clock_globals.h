#ifndef CLOCK_GLOBALS_H
#define CLOCK_GLOBALS_H

#include <pthread.h>
#include "./timer_globals.h"

/**
 * @brief Variables used for syncronization between timers and clock
 * 
 */

extern pthread_mutex_t clock_mutex;
extern pthread_cond_t timer_cond;
extern pthread_cond_t free_timer_tick;
extern int done_timers;

/**
 * @brief  Clock struct
 * 
 */

struct Clock { 
    int id; 
    int simulating_hz;
};


/**
 * @brief Based on the defined clock configuration it creates a clock that runs at an specified Hz rate
 * 
 * @param defined_clock The clock that is going to be generated
 * @return void
 * 
 */
void *create_clock( void *args );

#endif

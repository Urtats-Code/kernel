#ifndef TIMER_GLOBALS_H
#define TIMER_GLOBALS_H

#define TIMER_NUM 8
 

/**
 * @brief Timer struct
 * 
 */
struct Timer {
    int id;
    int clock_hz; 
    int signal_time; 
};


/**
 * @brief Creates a timer process that is synchronized with the clock
 * 
 * @param args 
 * @return void 
 */
void *create_timer( void *args ); 
void *create_scheduler_timer( void *args ); 

#endif



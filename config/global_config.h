#ifndef GLOBAL_CONFIG
#define GLOBAL_CONFIG

// Amount of timers
#define TIMER_NUM 20

// Process geneartor max and min process duration
#define MAX_PROCESS_DURATION 20
#define MIN_PROCESS_DURATION 5

// This line defines how much quantum each process gets when it's created 
#define QUANTUM_TIME 4

// Scheduler policy usage
#define RR 0 
#define SJF 1 
#define POLICY SJF

// PC simulation configuration
#define CPU_NUM 4
#define BASE_CORE_NUM 4 
#define BASE_THREAD_NUM 4


// Info visualization
#define SHOW_PC_CONFIG 0
#define SHOW_WHEN_TIMER_SCHEDULES 0
#define SHOW_WHEN_PROCESS_IS_CREATED 0 
#define SHOW_THREAD_SCHEDULE_PROCESS 0 
#define SHOW_PROCESS_LIST 0


#endif

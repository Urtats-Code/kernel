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

// Memory configuraiton

#define PAGE_SIZE 4             //  KB 
#define PHYSICAL_MEMORY_SIZE 64 //  MB
#define VIRTUAL_ADDRESS_SIZE 32 //  bit 

#define SECONDARY_STORAGE_ROOT "../../secondary_storage/" // USE ABSOLUTE ROOT, OR BASED ON THE POSITION ON THE loader.c FILE LOCATION


// Info visualization
#define SHOW_PC_CONFIG 0
#define SHOW_WHEN_TIMER_SCHEDULES 0
#define SHOW_WHEN_PROCESS_IS_CREATED 0 
#define SHOW_THREAD_SCHEDULE_PROCESS 0
#define SHOW_PROCESS_LIST 0
#define SHOW_CLOCK_CONFIG 0
#define SHOW_MEMORY_CONFIG 1




#endif

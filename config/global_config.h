#ifndef GLOBAL_CONFIG
#define GLOBAL_CONFIG

// =====================
// Clock Configuration
// =====================
#define CLOCK_HZ            50

// =====================
// Timer Configuration
// =====================

// Defines the number of timers used in the system.
#define TIMER_NUM           4

// =====================
// Process Duration Configuration
// =====================

// Defines the maximum and minimum duration for process generation.

#define MAX_PROCESS_DURATION 20
#define MIN_PROCESS_DURATION 5

// =====================
// Quantum Time Configuration
// =====================

// Defines the quantum time allocated to each process upon creation.

#define QUANTUM_TIME        4

// =====================
// Scheduler Policy Configuration
// =====================

// Defines the scheduling policies available and the default policy in use.

#define RR                  0 
#define SJF                 1 
#define POLICY              RR

// =====================
// PC Simulation Configuration
// =====================

// Defines the number of CPUs and the base configuration for cores and threads.

#define CPU_NUM             1
#define BASE_CORE_NUM       4 
#define BASE_THREAD_NUM     4

// =====================
// Memory Configuration
// =====================

// Defines the memory parameters including page size and memory sizes.

#define PAGE_SIZE            4          //  KiB 
#define PHYSICAL_MEMORY_SIZE 64         //  MiB
#define VIRTUAL_ADDRESS_SIZE 32         //  bit 

// =====================
// Storage Configuration
// =====================

// Defines the root path for secondary storage based on the loader.c file location.

#define SECONDARY_STORAGE_ROOT "src/disk/" 

// =====================
// Info Visualization Configuration
// =====================

// Defines flags for visualizing various configurations and events in the system.

#define SHOW_PC_CONFIG                  0
#define SHOW_WHEN_TIMER_SCHEDULES       0
#define SHOW_WHEN_PROCESS_IS_CREATED    0
#define SHOW_THREAD_SCHEDULE_PROCESS    0
#define SHOW_PROCESS_LIST               0
#define SHOW_CLOCK_CONFIG               0
#define SHOW_MEMORY_CONFIG              0
#define SHOW_VIRTUAL_MEMORY_STATE       0
#define SHOW_PHYSICAL_MEMORY_STATE      0
#define SHOW_FILE_LOADING_INFO          0
#define SHOW_CHUNK_INFO                 0
#define SHOW_LOADING_ERROR_STATE        0
#define SHOW_READING_LINE               0

#endif

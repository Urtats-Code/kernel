#include "global_config.h"

#ifndef PC_GLOBALS
#define PC_GLOBALS


extern struct PC pc; 

struct PC { 
    int id; 
    int cpu_num; 
    struct CPU *cpu_list; 
};

struct CPU {
    int id; 
    int core_num;
    struct Core *core_list;    
};

struct Core {
    int id; 
    int thread_num; 
    struct Thread *thread_list; 
};


// Core functions

struct PC initialize_pc(void);
struct CPU* initialize_cpus(int cpu_num);
struct Core* initialize_cores(int core_num);
struct Thread* initialize_threads( int thread_num ); 

// Utils

void fill_core_per_cpu(void);
void free_pc_memory( struct PC *pc );

void print_thread(struct Thread *thread, int thread_count);
void print_core(struct Core *core, int core_count);
void print_cpu(struct CPU *cpu, int cpu_count);
void print_pc(struct PC *pc);

#endif

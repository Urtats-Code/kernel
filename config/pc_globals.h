#ifndef CLOCK_GLOBALS_H
#define CLOCK_GLOBALS_H

#define CPU_NUM 4

struct CPU {
    int id; 
    int core_num;
    struct Core *core_head;
    struct CPU *next_CPU;     
};

struct Core {
    int id; 
    struct Thread *thread_head; 
    struct Core *next_core;     
};

#endif

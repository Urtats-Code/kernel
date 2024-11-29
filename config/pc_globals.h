#ifndef PC_GLOBALS
#define PC_GLOBALS

#define CPU_NUM 4
#define BASE_CORE_NUM 4 

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
    struct Thread *thread_list; 
};


// Core functions

struct PC initialize_pc(void);
struct CPU* initialize_cpus(int cpu_num);
struct Core* initialize_cores(int core_num);

// Utils

void fill_core_per_cpu(void);
void free_pc_memory( struct PC *pc );

void print_core(struct Core *core, int core_count);
void print_cpu(struct CPU *cpu, int cpu_count);
void print_pc(struct PC *pc);


#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Configuration files
#include "../config/pc_globals.h"
#include "../config/thread_globals.h"

int core_per_cpu[CPU_NUM] = { 0, 0, 0, 0 };

struct PC initialize_pc( void ) {

    struct PC pc;
    struct CPU* cpu_list;

    cpu_list = initialize_cpus(CPU_NUM);

    pc.cpu_num = CPU_NUM;   
    pc.id = 1;
    pc.cpu_list = cpu_list;
    
    return pc;
}

struct CPU* initialize_cpus(int cpu_num) {
    int cpu_index;
    struct CPU* cpu_list = malloc(cpu_num * sizeof(struct CPU));

    if (!cpu_list) {
        perror("Failed to allocate memory for CPU list");
        exit(EXIT_FAILURE);
    }

    fill_core_per_cpu();

    for (cpu_index = 0; cpu_index < cpu_num; cpu_index++) {
        struct CPU* new_cpu = &cpu_list[cpu_index];

        new_cpu->id = cpu_index;
        new_cpu->core_num = core_per_cpu[cpu_index];
        new_cpu->core_list = initialize_cores(new_cpu->core_num);

    }

    return cpu_list;
}


struct Core* initialize_cores(int core_num) {
    int core_index;
    struct Core* core_list = malloc(core_num * sizeof(struct Core));

    if (!core_list) {
        perror("Failed to allocate memory for Core list");
        exit(EXIT_FAILURE);
    }

    for (core_index = 0; core_index < core_num; core_index++) {
        struct Core* new_core = &core_list[core_index];

        new_core->id = core_index;
        new_core->thread_num = BASE_THREAD_NUM;
        new_core->thread_list = initialize_threads( BASE_THREAD_NUM );

    }

    return core_list;
}

struct Thread* initialize_threads( int thread_num ){

    int thread_index;
    struct Thread* thread_list = malloc(thread_num * sizeof(struct Thread));

    if (!thread_list) {
        perror("Failed to allocate memory for Thread list");
        exit(EXIT_FAILURE);
    }

    for( thread_index = 0; thread_index < thread_num; thread_index ++ ){

        struct Thread* new_hardware_thread = &thread_list[ thread_index ]; 

        new_hardware_thread -> id = thread_index; 
        new_hardware_thread -> free =  1; 
        new_hardware_thread -> PC   = -1; 
        new_hardware_thread -> IR   = -1; 
        new_hardware_thread -> PTBR = -1; 

    }

    return thread_list;

} 


void fill_core_per_cpu(void) {
    for (int i = 0; i < CPU_NUM; i++) {
        core_per_cpu[i] = BASE_CORE_NUM;
    }
}





void free_pc_memory(struct PC *pc) {
    
    int cpu_index;

    for (cpu_index = 0; cpu_index < pc->cpu_num; cpu_index++) {
        struct CPU *current_cpu = &(pc->cpu_list[cpu_index]);

        free(current_cpu->core_list);
    }

    free(pc->cpu_list);
    free(pc);

}

void print_thread(struct Thread *thread, int thread_count) {
    printf("| Thread ID | Status |\n");
    for (int i = 0; i < thread_count; i++) {
        printf("| %7d | %s\n", thread[i].id, thread[i].free ? "Free" : "In Use");
    }
}

void print_core(struct Core *core, int core_count) {
    printf("| Core ID | Threads |\n");
    for (int i = 0; i < core_count; i++) {
        printf("| %7d | %s\n", core[i].id, core[i].thread_list ? "Available" : "None");
        if (core[i].thread_list) {
            print_thread(core[i].thread_list, BASE_THREAD_NUM);
        }
    }
}

void print_cpu(struct CPU *cpu, int cpu_count) {
    printf("| CPU ID | Cores |\n");
    for (int i = 0; i < cpu_count; i++) {
        printf("| %5d | %d |\n", cpu[i].id, cpu[i].core_num);
        print_core(cpu[i].core_list, cpu[i].core_num);
    }
}

void print_pc(struct PC *pc) {
    printf("| PC ID | CPUs |\n");
    printf("| %5d | %d |\n", pc->id, pc->cpu_num);
    print_cpu(pc->cpu_list, pc->cpu_num);
}

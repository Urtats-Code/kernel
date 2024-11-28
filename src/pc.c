#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Configuration files
#include "../config/pc_globals.h"

int core_per_cpu[CPU_NUM];

struct PC initialize_pc() {

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

        struct CPU* new_cpu = malloc( sizeof( struct CPU ) );

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

        struct Core* new_core = malloc( sizeof( struct Core ) );

        new_core->id = core_index;
        new_core->thread_list = NULL;

    }

    return core_list;
}


void fill_core_per_cpu(void) {
    for (int i = 0; i < CPU_NUM; i++) {
        if (core_per_cpu[i] == 0) {
            core_per_cpu[i] = BASE_CORE_NUM;
        }
    }
}


void free_pc_memory( struct PC *pc ){

    int cpu_index, core_index; 

    for( cpu_index = 0; cpu_index < pc -> cpu_num; cpu_index ++ ){
        
        struct CPU *current_cpu = &( pc -> cpu_list[ cpu_index ] ); 

        for( core_index = 0; core_index <  current_cpu -> core_num; core_index ++ ){

            struct Core *current_core = &( current_cpu -> core_list[ core_index ] );

            free( current_core );

        }

        free( current_cpu -> core_list );
        free( current_cpu );
    }

    free( pc -> cpu_list );
    free( pc );

}

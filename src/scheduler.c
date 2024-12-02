// Libraries

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Configuration files

#include "../config/scheduler_globlas.h"
#include "../config/process_globals.h"
#include "../config/thread_globals.h"
#include "../config/pc_globals.h"

void policy_RR( struct Thread *thread ){ 

    if( thread -> free ){ 

        thread->free = 1; 
        thread->pcb = get_process_list_head(); 

    } else { 

        thread -> pcb -> duration --;
        thread -> pcb -> quantum --;

        if( thread -> pcb -> duration == 0 ){  // Execution finished 
            thread -> free = 0; 
            return; 
        } 
        
        if ( thread -> pcb -> quantum == 0 ){
            thread -> free = 0; 
            thread -> pcb -> quantum = QUANTUM_TIME;
            add_to_process_list( thread -> pcb );
            return; 
        }

    }

}

void policy_SFJ( struct Thread *thread ) { 


} 

void schedule_with( struct PC *pc, void( *callback ) ( struct Thread *thread ) ){

    int cpu_index, core_index, thread_index; 

    for( cpu_index = 0; cpu_index < CPU_NUM; cpu_index++){

        struct CPU current_cpu = pc -> cpu_list[ cpu_index ]; 

        for( core_index = 0; core_index < current_cpu.core_num; core_index++){

            struct Core current_core = current_cpu.core_list[ core_index ]; 

            for( thread_index = 0; thread_index < current_core.thread_num; thread_index++){

                struct Thread *current_thread = &current_core.thread_list[thread_index];
                callback(current_thread);

            }

        }
    }

}

void schedule_process( void ) {

    if( POLICY == SFJ ){
        schedule_with( &pc, policy_SFJ ); 
    }

    if( POLICY == RR ){
        schedule_with( &pc, policy_RR ); 
    }

}

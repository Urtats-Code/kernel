// Libraries

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Configuration files

#include "../config/scheduler_globlas.h"
#include "../config/process_globals.h"
#include "../config/thread_globals.h"
#include "../config/pc_globals.h"

int policy_RR( struct Thread *thread ){ 

    if( thread == NULL ) return 1; 


    if( thread -> free ){ 

        struct PCB *checking_pcb = get_process_list_head(); 

        if( checking_pcb != NULL ){
            thread->free = 0; 
            thread->pcb = checking_pcb;
        }


    } else { 

        thread -> pcb -> duration --;
        thread -> pcb -> quantum --;


        if( SHOW_THREAD_SCHEDULE_PROCESS ){


            printf(" At thread %d \n", thread -> id );
            printf(" PID | STATE | PRIORITY | QUANTUM | DURATION \n");
            printf("%d\t%d\t%d\t\t%d\t%d\n",
                   thread-> pcb ->pid,
                   thread-> pcb ->state,
                   thread-> pcb ->priority,
                   thread-> pcb ->quantum,
                   thread-> pcb ->duration);

        }


        if( thread -> pcb -> duration <= 0 ){  // Execution finished 
            thread -> free = 1; 
            return 0; 
        } 
        else if ( thread -> pcb -> quantum <= 0 ){
            thread -> free = 1; 
            thread -> pcb -> quantum = QUANTUM_TIME;
            add_to_process_list( thread -> pcb );
            return 0; 
        }

    }

    return 0;

}


int policy_SJF( struct Thread *thread ){

    if( thread == NULL ) return 1; 


    if( thread -> free ){ 

        struct PCB *checking_pcb = get_process_list_head(); 

        if( checking_pcb != NULL ){
            thread->free = 0; 
            thread->pcb = checking_pcb;
        }

    } else { 

        thread -> pcb -> duration --;


        if( SHOW_THREAD_SCHEDULE_PROCESS ){


            printf(" At thread %d \n", thread -> id );
            printf(" PID | STATE | PRIORITY | QUANTUM | DURATION \n");
            printf("%d\t%d\t%d\t\t%d\t%d\n",
                   thread-> pcb ->pid,
                   thread-> pcb ->state,
                   thread-> pcb ->priority,
                   thread-> pcb ->quantum,
                   thread-> pcb ->duration);

        }


        if( thread -> pcb -> duration <= 0 ){  // Execution finished 
            thread -> free = 1; 
            return 0; 
        } 

    }

    return 0;

}



void schedule_with( struct PC *pc, int( *callback ) ( struct Thread *thread ) ){

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

    if( POLICY == SJF ){
        schedule_with( &pc, policy_SJF ); 
    }

    if( POLICY == RR ){
        schedule_with( &pc, policy_RR ); 
    }

}

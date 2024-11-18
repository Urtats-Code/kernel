// Libraries

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Configuration files

#include "../config/process_globals.h"

// Initialize extern variables

struct PCB *head_pcb = NULL; 
int last_pid = 0; 


// Main functions

void *create_process( void ) { 

    struct PCB *new_PCB = ( struct PCB * ) malloc( sizeof(struct PCB) );

    if (new_PCB == NULL) {
        perror("Failed to allocate memory for PCB");
        exit(EXIT_FAILURE);
    }

    *new_PCB = create_new_PCB(); 
    add_to_process_list( new_PCB );

    return NULL;
}

void add_to_process_list( struct PCB *new_PCB ){

    new_PCB->next_PCB =  head_pcb;
    head_pcb = new_PCB;

    print_process_list();

} 

// Auxiliary functions

struct PCB create_new_PCB( void ) { 

    int pid      = last_pid++; 
    int state    = 0; 
    int priority = 0; 
    int quantum  = 0; 
    int duration = MIN_PROCESS_DURATION + (rand() % ( MAX_PROCESS_DURATION - MIN_PROCESS_DURATION )); // Simple formula to generate numbers in between a range

    struct PCB new_PCB = { pid, state, priority, quantum, duration, NULL, NULL }; 

    return new_PCB; 

}

void free_all_pcbs( void ) {

    struct PCB *current = head_pcb;

    while (current != NULL) {
        struct PCB *temp = current;
        current = current->next_PCB;
        free(temp);
    }

    head_pcb = NULL;
}


void print_process_list( void ) {

    struct PCB *current = head_pcb; 

    printf("Process List:\n");
    printf("PID\tState\tPriority\tQuantum\tDuration\n");
    printf("-----------------------------------------------\n");

    while (current != NULL) { 
        printf("%d\t%d\t%d\t\t%d\t%d\n",
               current->pid,
               current->state,
               current->priority,
               current->quantum,
               current->duration);

        current = current->next_PCB; 
    }

}

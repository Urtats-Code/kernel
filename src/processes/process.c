// Libraries

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Configuration files

#include "../../config/process_globals.h"

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

    if( POLICY == SJF ){
         head_pcb =  sort_process_list_by_duration( head_pcb );
    }

    if( SHOW_PROCESS_LIST ){
        print_process_list();
    }


} 

// Auxiliary functions

struct PCB create_new_PCB( void ) { 

    int pid      = last_pid++; 
    int state    = 0; 
    int priority = 0; 
    int quantum  = QUANTUM_TIME; 
    int duration = MIN_PROCESS_DURATION + (rand() % ( MAX_PROCESS_DURATION - MIN_PROCESS_DURATION )); // Simple formula to generate numbers in between a range

    struct PCB new_PCB = { pid, state, priority, quantum, duration, NULL, NULL }; 

    return new_PCB; 

}



struct PCB *get_process_list_head(void) { 
    
    if (head_pcb == NULL) {
        return NULL;  
    }

    struct PCB *prev_pcb = head_pcb;
    struct PCB *current = head_pcb->next_PCB;

    
    if (current == NULL) {
        head_pcb = NULL;
        return prev_pcb;  
    }

    
    while (current->next_PCB != NULL) {
        prev_pcb = current;
        current = current->next_PCB;
    }

    
    prev_pcb->next_PCB = NULL;

    return current;  
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
struct PCB *sort_process_list_by_duration(struct PCB *head) { 
 
    if (head == NULL || head->next_PCB == NULL)
        return head;

    struct PCB *second = split(head);

    head = sort_process_list_by_duration(head);
    second = sort_process_list_by_duration(second);

    return merge(head, second);
}

struct PCB *merge(struct PCB *first, struct PCB *second) { 
    if (first == NULL) return second;
    if (second == NULL) return first;

    if (first->duration > second->duration) {     
        first->next_PCB = merge(first->next_PCB, second);
        return first;        
    } else {
        second->next_PCB = merge(first, second->next_PCB);
        return second;
    }
}

struct PCB *split(struct PCB *head) { 
    struct PCB *fast = head;
    struct PCB *slow = head;

    while (fast != NULL && fast->next_PCB != NULL) {
        fast = fast->next_PCB->next_PCB;
        if (fast != NULL) {
            slow = slow->next_PCB;
        }
    }

    struct PCB *temp = slow->next_PCB;
    slow->next_PCB = NULL;
    return temp;
}



#ifndef PROCESS_GLOBALS_H
#define PROCESS_GLOBALS_H

#define MAX_PROCESS_DURATION 20
#define MIN_PROCESS_DURATION 5 

extern int last_pid; 


struct MemoryManagement {
  uint32_t data;
  uint32_t code;
  uint32_t pgb;
};

struct PCB {
  int pid;
  int state;
  int priority;
  int quantum;
  int duration;
  struct MemoryManagement *mm;
  struct PCB *next_PCB; 
};

// Functions 

// Main Functions

void *create_process( void );
void add_to_process_list( struct PCB *new_PCB );

// Auxiliary functions 

struct PCB create_new_PCB( void ); 
void print_process_list( void );
void free_all_pcbs( void );


#endif



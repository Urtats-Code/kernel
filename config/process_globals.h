#ifndef PROCESS_GLOBALS_H
#define PROCESS_GLOBALS_H

#define MAX_PROCESS_DURATION 20
#define MIN_PROCESS_DURATION 5

// This line defines how much quantum each process gets when it's created 
// Recomendation: 
// - Time sensitve systmes: 10 - 20 ms 
// - Throughput oriented  systmes: 50 - 100 ms 
#define QUANTUM_TIME 10

#define RR 0 
#define SFJ 1 
#define POLICY RR

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
struct PCB *get_process_list_head( void );
void print_process_list( void );
void free_all_pcbs( void );
// Sorting 

struct PCB *sort_process_list_by_duration( struct PCB *head );
struct PCB *merge( struct PCB *first, struct PCB *second );
struct PCB *split( struct PCB *head );

#endif



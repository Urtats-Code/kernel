// Configuration files

#include "../config/process_globals.h"
#include "../config/thread_globals.h"
#include "../config/pc_globals.h"

#ifndef SCHEDULER_GLOBALS
#define SCHEDULER_GLOBALS

struct PC; 
struct Thread;

void schedule_process( void ); 
void policy_RR(struct Thread *thread); 
void policy_SFJ(struct Thread *thread); 
void schedule_with(struct PC *pc, void (*callback)(struct Thread *thread)); 

#endif

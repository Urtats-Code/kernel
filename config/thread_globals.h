// Libraries

#include <stdint.h>

// Configuration files

#include "process_globals.h"
#include "memory_globals.h"

#ifndef THREAD_GLOBALS
#define THREAD_GLOBALS


struct Thread {
  int id;
  int free;
  uint32_t PC;
  uint32_t IR;
  uint32_t PTBR;
  struct PCB *pcb;
};

struct TLB{ 
  struct Page *page_list; 
};

struct MMU{ 
  struct TLB tlb; 
  uint32_t checking_virtual_addres; 
};

#endif

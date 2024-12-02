// Libraries

#include <stdint.h>

// Configuration files

#include "process_globals.h"

#ifndef CLOCK_GLOBALS_H
#define CLOCK_GLOBALS_H

struct Thread {
  int id;
  int free;
  uint32_t PC;
  uint32_t IR;
  uint32_t PTBR;
  struct PCB *pcb;
};

#endif

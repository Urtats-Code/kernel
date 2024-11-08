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
  struct MemoryManagement mm;
}
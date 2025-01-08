# Simple Kernel

**Disclaimer**: This project is strictly for educational purposes and is not intended for production use. The code may not function perfectly or seamlessly, and no guarantees are made regarding its reliability or stability in real-world applications.

This project aims to simulate the fundamental functionality of an operating system kernel by artificially generating signals and processes similar to those a kernel would handle. The purpose is to provide an educational demonstration of core kernel concepts and operations, rather than a fully functional or production-ready system.

## Execution Instructions

To run this project, follow these simple steps:

1. Compile the project:
   ```bash
   make
   ```

2. Run the project:
   ```bash
   make run
   ```

After compiling and executing, the project will generate several `.o` files in the filesystem. Once you are finished with execution and testing, it is recommended to clean up these  files by running:

```bash
make clean
```

This will remove any temporary files and keep your project directory tidy.



## Configuration Overview

The `global_config.h` file allows you to customize the kernel’s behavior and adjust simulation parameters. Below is a breakdown of each configuration option:

---

### **Timer Configuration**
- `TIMER_NUM [NUMBER]`  
  **Description:** Specifies the total number of timers available in the simulation. Timers are used for scheduling and process management.

---

### **Process Generator Configuration**
- `MAX_PROCESS_DURATION [MAX_NUM]`  
  **Description:** Sets the maximum duration (in arbitrary time units) for a process to complete.

- `MIN_PROCESS_DURATION [MIN_NUM]`  
  **Description:** Sets the minimum duration (in arbitrary time units) for a process to complete.

---

### **Quantum Time Configuration**
- `QUANTUM_TIME [INTENDED_NUMBER]`  
  **Description:** Defines the time slice (quantum) allocated to each process in the Round Robin (RR) scheduling policy. This determines how long a process runs before being preempted.

---

### **Scheduler Policy Selection**
- `RR 0`  
  **Description:** Round Robin scheduling policy (preemptive, time-sliced scheduling).

- `SJF 1`  
  **Description:** Shortest Job First scheduling policy (non-preemptive, selects the process with the shortest duration).

- `POLICY [POLICY]`  
  **Description:** Specifies the scheduler policy in use.  
  **Current Setting:** `SJF` (Shortest Job First).  
  To switch to Round Robin, change this line to:  
  ```c
  POLICY RR
  ```

---

### **Processor (PC) Simulation Configuration**
- `CPU_NUM [INTENDED_NUM]`  
  **Description:** Specifies the number of CPUs (or processing cores) in the simulation.

- `BASE_CORE_NUM [INTENDED_NUM]`  
  **Description:** Defines the base number of cores available in the system.

- `BASE_THREAD_NUM [INTENDED_NUM]`  
  **Description:** Sets the number of hardware threads per core in the simulation.

---

### **Information Visualization Configuration**
These flags control if any message is required for a better visualization of the kernel functionality. 

- `SHOW_PC_CONFIG 0`  
  **Description:** Displays the system configuration (CPUs, cores, threads) if set to `1`.

- `SHOW_WHEN_TIMER_SCHEDULES 0`  
  **Description:** Displays a message when a timer triggers scheduling if set to `1`.

- `SHOW_WHEN_PROCESS_IS_CREATED 0`  
  **Description:** Displays a message whenever a new process is created if set to `1`.

- `SHOW_THREAD_SCHEDULE_PROCESS 0`  
  **Description:** Displays a message when a thread is assigned a process if set to `1`.

- `SHOW_PROCESS_LIST 0`  
  **Description:** Displays the current list of processes when one is created if set to `1`.

**Note:** Set any of these flags to `1` to enable detailed logging and visualization during the simulation.

---

This configuration file is a way to tailor the kernel simulation to your needs, whether for educational purposes, debugging, or performance evaluation. Adjust the settings as necessary to suit your desired behavior.
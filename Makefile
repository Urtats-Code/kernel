# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -pthread

# Files 
TIME_SRCS      	= ./src/time/clock.c ./src/time/timer.c
PROCESS_SRCS   	= ./src/processes/process.c
EXECUTE_SRCS   	= ./src/pc/execute/execute.c
PC_SRCS        	= ./src/pc/CPU/pc.c
MEMORY_SRCS    	= ./src/pc/memory/calculations.c ./src/pc/memory/physical_mem.c ./src/pc/memory/virtual_mem.c ./src/pc/memory/physical_virtual_memory.c  ./src/pc/memory/loader.c
SRCS           	= $(PC_SRCS)  $(EXECUTE_SRCS)  $(PROCESS_SRCS) $(MEMORY_SRCS) $(TIME_SRCS) ./src/scheduling/scheduler.c ./src/main.c
OBJS 			= $(SRCS:.c=.o)
EXEC 			= kernel

all: $(EXEC)

# Executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# Clean case 
clean:
	rm -f $(OBJS) $(EXEC)
	
# Run case
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run

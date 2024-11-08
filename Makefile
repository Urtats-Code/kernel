# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -pthread

# Files 
SRCS = ./src/clock.c  ./src/main.c 
OBJS = $(SRCS:.c=.o)
EXEC = kernel

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

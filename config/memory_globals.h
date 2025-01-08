// Libraries 
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Config files 
#include "global_config.h"
#include "process_globals.h"

#ifndef MEMORY_GLOBALS_H
#define MEMORY_GLOBALS_H

#define KB 1024

struct EmptySpace { 
    void* start_address; 
    long available_space; 
    struct EmptySpace *next; 
};

struct MemoryAllocator { 
    struct EmptySpace *free_list; 
};

struct PhysicalMemory { 
    int frame_num;              
    int memory_size_MB;         
    uint8_t *memory_list;       // Each position of the array is 1 Byte, this means it's value can go from 0 255 
};

struct PageTableEntry {
    int frame_num;  
    int valid;      
};

struct PageTable {
    struct PageTableEntry *entries; 
    int size;     
};

struct VirtualMemory { 
    int page_num;              
    struct PageTable *page_table;  
};

struct VirtualAddress { 
    uint32_t page_num;  
    uint32_t offset;    
};

// Extern Variables

extern struct PhysicalMemory    *physical_memory; 
extern struct VirtualMemory     *virtual_memory; 

// Calculations 

int calculate_offset(void);
int calculate_physical_memory_bits(void);
int calculate_frame_num(void);
int calculate_page_num(void);

// Physical Memory Function Prototypes


void physical_virtual_memory_mapping_calculations(void);
void create_physical_memory( int frame_num );
void initialize_physical_memory(void);

// Virtual Memory Function Prototypes

void create_virtual_memory(int page_num);
void initialize_virtual_memory(void);
void create_load_process(char *file_name);


// Utils 

void free_physical_virtual_memory( void );
void print_virtual_memory_state(void);
void print_physical_memory_state(void);
void print_file_loading_info(const char *file_name, long file_size);
void print_loading_error_state(long bytes_loaded, long total_bytes);
void print_read_chunk_info(long current_offset, size_t chunk_size, long bytes_loaded, long total_bytes);




int find_free_frame(void);
void load_file_into_memory(const char *file_name);
int map_page_to_frame(int page_num, int frame_num);
void read_file_chunk(FILE *file, long offset, uint8_t *dest, size_t size, long bytes_loaded, long total_bytes);

// Loader  section 

struct PCB* initialize_pcb(void);
struct MM* initialize_mm(void);
char* create_file_path(const char *file_name);
long handle_file_operations(const char *route);
void setup_memory_mapping(struct PCB *pcb, long file_size);
void create_load_process(char *file_name);


#endif 

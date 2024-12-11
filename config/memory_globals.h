// Libraries 
#include <stdint.h>

// Config files 
#include "global_config.h"

#ifndef MEMORY_GLOBALS_H
#define MEMORY_GLOBALS_H

struct Frame {
    int id;            
    int is_occupied;   
    int page_num;      
};

struct PhysicalMemory { 
    int frame_num;              
    int memory_size_MB;         
    struct Frame *frame_list; 
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

#endif 

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// Config files 
#include "../../../config/memory_globals.h"

struct VirtualMemory  *virtual_memory;

/**
 *
 *  Virtual Memory
 * 
 */

void create_virtual_memory( int page_num ) { 

    if (virtual_memory == NULL) {
        
        virtual_memory = malloc(sizeof(struct VirtualMemory));

        if (virtual_memory == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }

    }

    virtual_memory -> page_num          = page_num; 

    initialize_virtual_memory();

} 

void initialize_virtual_memory( void ) {
    
    virtual_memory -> page_table = malloc(sizeof(struct PageTable));

    if (virtual_memory -> page_table == NULL) {
        printf("Page table allocation failed!\n");
        return;
    }

    virtual_memory -> page_table -> size    =  virtual_memory -> page_num;
    
    virtual_memory -> page_table -> entries = ( struct PageTableEntry * ) malloc( virtual_memory -> page_table -> size * sizeof( struct PageTableEntry ) );

    for (int i = 0; i < virtual_memory -> page_table -> size; i++ ) {
        virtual_memory ->  page_table -> entries[i].frame_num   = -1;  
        virtual_memory ->  page_table -> entries[i].valid       = 0;       
    }
}


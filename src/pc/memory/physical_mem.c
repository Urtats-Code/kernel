// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

// Config files 
#include "../../../config/memory_globals.h" // Ensure this header has the necessary definitions

struct PhysicalMemory *physical_memory; 

/**
 *
 *  Physical Memory
 * 
 */

void create_physical_memory( int frame_num ) { 


    if (physical_memory == NULL) {
        
        physical_memory = malloc(sizeof( struct PhysicalMemory ));

        if (physical_memory == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }

    }

    physical_memory -> frame_num        = frame_num;     
    physical_memory -> memory_size_MB   = PHYSICAL_MEMORY_SIZE; 


    initialize_physical_memory( ); 

} 


void initialize_physical_memory( void ) { 

    physical_memory -> memory_list = malloc( sizeof( uint8_t ) * physical_memory -> frame_num   * PAGE_SIZE * KB ); // Memory is represented as an arrya of bytes

    if (physical_memory->memory_list == NULL) {
        fprintf(stderr, "Failed to allocate physical memory\n");
        exit(EXIT_FAILURE);
    }

    memset(physical_memory->memory_list, 0, physical_memory -> frame_num *  PAGE_SIZE * KB );

}

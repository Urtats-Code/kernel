// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

    int i;

    physical_memory -> frame_list = ( struct Frame * ) malloc( physical_memory -> frame_num * sizeof( struct Frame ) );

    for ( i = 0; i < physical_memory -> frame_num; i++ ) {

        physical_memory -> frame_list[i].id             = i;  
        physical_memory -> frame_list[i].is_occupied    = 0; 
        physical_memory -> frame_list[i].page_num       = -1;   

    }

}

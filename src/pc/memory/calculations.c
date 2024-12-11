#include <math.h>

// Config files 
#include "../../../config/memory_globals.h"

/**
 *
 *  Calculations
 * 
 */

int calculate_offset( void ) { 

    // Calcaulte the offset

    double using_bytes = log2( PAGE_SIZE );
    int offset = using_bytes + 10;  

    return offset; 

} 

int calculate_physical_memory_bits( void ) { 
    
    int physical_memory_bits = log2( PHYSICAL_MEMORY_SIZE ); 
    physical_memory_bits += 20; 

    return physical_memory_bits;

}


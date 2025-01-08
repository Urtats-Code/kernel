#include <math.h>

// Config files 
#include "../../../config/memory_globals.h"

/**
 *
 *  Calculations
 * 
 */

int calculate_offset(void) { 
    return log2(PAGE_SIZE * KB);  // If PAGE_SIZE is 4, this gives us 12 bits (for 4KB pages)
}

int calculate_physical_memory_bits( void ) { 
    
    int physical_memory_bits = log2( PHYSICAL_MEMORY_SIZE ); 
    physical_memory_bits += 20; // Asuming memory size in MiB 

    return physical_memory_bits;

}

int calculate_page_num(void) {
    // For 64MB physical memory with 4KB pages:
    // 64MB = 64 * 1024 * 1024 bytes
    // Number of pages = (64 * 1024 * 1024) / (4 * 1024) = 16384 pages
    return (PHYSICAL_MEMORY_SIZE * KB * KB) / (PAGE_SIZE * KB);
}

int calculate_frame_num( void ){

    int size_in_KiB = PHYSICAL_MEMORY_SIZE * KB; // Asumming KiB as page size 
    return size_in_KiB / PAGE_SIZE; 

} 

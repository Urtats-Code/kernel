// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// Configuration files
#include "../../../config/memory_globals.h"


void physical_virtual_memory_mapping_calculations( void ){ 

    int page_num = calculate_page_num();
    int frame_num = calculate_frame_num();

    

    if( SHOW_MEMORY_CONFIG ){

        printf("==============================================\n");
        printf("|            Memory Information               |\n");
        printf("==============================================\n");
        printf("| %-30s | %10d |\n", "Page Number", page_num);
        printf("| %-30s | %10d |\n", "Frame Number", frame_num);
        printf("| %-30s | %10d KB |\n", "Frame Size", PAGE_SIZE);
        printf("| %-30s | %10d MB |\n", "Physical Memory Size", PHYSICAL_MEMORY_SIZE);
        printf("| %-30s | 2 ^ %d Bytes |\n", "Virtual Memory Size ( )", VIRTUAL_ADDRESS_SIZE);
        printf("| %-30s | %10d bits |\n", "Virtual Address Size", VIRTUAL_ADDRESS_SIZE);
        printf("==============================================\n");

    }



    create_physical_memory( frame_num ); 
    create_virtual_memory( page_num );


}  


void free_physical_virtual_memory( void ) {


    free( virtual_memory -> page_table -> entries );
    free( virtual_memory -> page_table );

    free( physical_memory -> memory_list );    
    free( virtual_memory );
    free( physical_memory );

}


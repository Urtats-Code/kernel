// Libraries
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Configuraiton files 
#include "../../../config/process_globals.h"
#include "../../../config/global_config.h"
#include "../../../config/memory_globals.h"
#include "../../../config/execute_globals.h"


void print_document_contents(struct PCB *pcb) {


    

    if (pcb == NULL || pcb->mm == NULL) {
        printf("Error: Invalid PCB or memory management structure\n");
        return;
    }




    struct PageTable *page_table = virtual_memory -> page_table;
    if (page_table == NULL) {
        printf("Error: Invalid page table\n");
        return;
    }



    uint32_t current_offset = 0;
    uint32_t current_page = 0;
    char line_buffer[LINE_SIZE + 1]; // for null termination 
    line_buffer[LINE_SIZE] = '\0';   

    if( SHOW_READING_LINE ){
        printf("\n=== Document Contents for Process %d ===\n", pcb->pid);
    }
    

    while (current_page < pcb->mm->data) {  

        uint32_t page_num = current_offset / (PAGE_SIZE * KB);
        uint32_t page_offset = current_offset % (PAGE_SIZE * KB);

        if (page_num != current_page) {
            current_page = page_num;
            if (current_page >= pcb->mm->data) {
                break;
            }
        }

        if (!page_table->entries[current_page].valid) {
            printf("Error: Invalid page table entry for page %u\n", current_page);
            break;
        }

        int frame_num = page_table->entries[current_page].frame_num;


        uint8_t *physical_addr = physical_memory->memory_list + 
                               (frame_num * PAGE_SIZE * KB) + 
                               page_offset;


        uint32_t bytes_until_page_end = (PAGE_SIZE * KB) - page_offset;
        uint32_t bytes_to_read = (LINE_SIZE < bytes_until_page_end) ? 
                                LINE_SIZE : bytes_until_page_end;


        memcpy(line_buffer, physical_addr, bytes_to_read);


        if( SHOW_READING_LINE ){
            printf("Line %u: %s\n", current_offset / LINE_SIZE + 1, line_buffer);
        }

        // Update offset for next line
        current_offset += LINE_SIZE;
    }
    
    if( SHOW_READING_LINE ){
        printf("=== End of Document ===\n");
    }
}


void print_first_pcb_document(void) {
    
    struct PCB *first_pcb = head_pcb;
    
    if (first_pcb == NULL) {
        printf("No processes in the PCB list\n");
        return;
    }

    if( SHOW_READING_LINE ){
        printf("Reading document from Process ID: %d\n", first_pcb->pid);
    }
    print_document_contents(first_pcb);
}
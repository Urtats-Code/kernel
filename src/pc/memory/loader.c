// Libraries
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Config files
#include "../../../config/memory_globals.h"





void print_virtual_memory_state(void) {
    printf("\n==============================================\n");
    printf("|          Virtual Memory State              |\n");
    printf("==============================================\n");
    printf("Total Pages: %d\n", virtual_memory->page_num);
    printf("Page Table Entries:\n");
    printf("| Page # | Frame # | Valid |\n");
    printf("-------------------------------\n");
    
    for (int i = 0; i < virtual_memory->page_table->size; i++) {
        if (virtual_memory->page_table->entries[i].valid) {
            printf("| %6d | %7d | %5d |\n", 
                i, 
                virtual_memory->page_table->entries[i].frame_num,
                virtual_memory->page_table->entries[i].valid);
        }
    }
    printf("==============================================\n");
}


void print_physical_memory_state(void) {
    printf("\n==============================================\n");
    printf("|          Physical Memory State             |\n");
    printf("==============================================\n");
    printf("Total Frames: %d\n", physical_memory->frame_num);
    printf("Memory Size: %d MB\n", physical_memory->memory_size_MB);
    
    int used_frames = 0;
    for (int i = 0; i < virtual_memory->page_table->size; i++) {
        if (virtual_memory->page_table->entries[i].valid) {
            used_frames++;
        }
    }
    
    printf("Used Frames: %d\n", used_frames);
    printf("Free Frames: %d\n", physical_memory->frame_num - used_frames);
    printf("Frame Size: %d KB\n", PAGE_SIZE);
    printf("==============================================\n");
}

void print_file_loading_info(const char *file_name, long file_size) {
    printf("\n==============================================\n");
    printf("|          File Loading Information          |\n");
    printf("==============================================\n");
    printf("File Name: %s\n", file_name);
    printf("File Size: %ld bytes\n", file_size);
    printf("Required Pages: %ld\n", (file_size + (PAGE_SIZE * KB - 1)) / (PAGE_SIZE * KB));
    printf("==============================================\n");
}

void print_loading_error_state(long bytes_loaded, long total_bytes) {
    printf("\n==============================================\n");
    printf("|          Loading Error State               |\n");
    printf("==============================================\n");
    printf("Bytes Loaded: %ld of %ld bytes\n", bytes_loaded, total_bytes);
    printf("Pages Loaded: %ld of %ld pages\n", 
           bytes_loaded / (PAGE_SIZE * KB),
           (total_bytes + (PAGE_SIZE * KB - 1)) / (PAGE_SIZE * KB));
    printf("Loading Progress: %.2f%%\n", 
           (bytes_loaded * 100.0) / total_bytes);
    printf("==============================================\n");
}


long get_file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    return size;
}

int find_free_frame(void) {

    
    for (int i = 0; i < physical_memory->frame_num; i++) {
        
        int frame_is_used = 0;
        int PAGE_TABLE_SIZE = virtual_memory->page_table->size;
        
        for (int j = 0; j < PAGE_TABLE_SIZE; j++) {
            if (virtual_memory->page_table->entries[j].valid && 
                virtual_memory->page_table->entries[j].frame_num == i) {
                frame_is_used = 1;
                break;
            }
        }
        
        if (!frame_is_used) {
            return i;
        }

    }
    return -1;
}

int map_page_to_frame(int page_num, int frame_num) {

    if (page_num >= virtual_memory->page_table->size || frame_num >= physical_memory->frame_num) {
        return -1;
    }
    
    virtual_memory->page_table->entries[page_num].frame_num = frame_num;
    virtual_memory->page_table->entries[page_num].valid = 1;
    
    return 0;
}

void read_file_chunk(FILE *file, long offset, uint8_t *dest, size_t size) {
    fseek(file, offset, SEEK_SET);
    fread(dest, 1, size, file);
}

void load_file_into_memory(const char *file_name) {
    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    long file_size = get_file_size(file);
    long bytes_remaining = file_size;
    int current_page = 0;
    long current_offset = 0;
    
    if (SHOW_FILE_LOADING_INFO) {
        print_file_loading_info(file_name, file_size);
    }
    
    if (SHOW_VIRTUAL_MEMORY_STATE) {
        printf("\nVirtual Memory State Before Loading:\n");
        print_virtual_memory_state();
    }
    
    if (SHOW_PHYSICAL_MEMORY_STATE) {
        printf("\nPhysical Memory State Before Loading:\n");
        print_physical_memory_state();
    }
    
    while (bytes_remaining > 0) {
        int free_frame = find_free_frame();
        if (free_frame == -1) {
            if (SHOW_LOADING_ERROR_STATE) {
                printf("\nError: No free frames available\n");
                print_loading_error_state(file_size - bytes_remaining, file_size);
            }
            fclose(file);
            return;
        }
        
        size_t bytes_to_read = (bytes_remaining > PAGE_SIZE * KB) ? 
                              PAGE_SIZE * KB : bytes_remaining;
        
        uint8_t *frame_addr = physical_memory->memory_list + (free_frame * PAGE_SIZE * KB);
        
        read_file_chunk(file, current_offset, frame_addr, bytes_to_read);
        
        if (map_page_to_frame(current_page, free_frame) < 0) {
            if (SHOW_LOADING_ERROR_STATE) {
                printf("\nError: Failed to map page to frame\n");
                print_loading_error_state(file_size - bytes_remaining, file_size);
            }
            fclose(file);
            return;
        }
        
        bytes_remaining -= bytes_to_read;
        current_offset += bytes_to_read;
        current_page++;
    }

    fclose(file);
    
    if (SHOW_FILE_LOADING_INFO) {
        printf("\nFile loaded successfully!\n");
        print_file_loading_info(file_name, file_size);
    }
    
    if (SHOW_VIRTUAL_MEMORY_STATE) {
        printf("\nVirtual Memory State After Loading:\n");
        print_virtual_memory_state();
    }
    
    if (SHOW_PHYSICAL_MEMORY_STATE) {
        printf("\nPhysical Memory State After Loading:\n");
        print_physical_memory_state();
    }
}


void create_load_process(char *file_name) {

    size_t route_size = strlen(SECONDARY_STORAGE_ROOT) + strlen(file_name) + 1;
    char *route = malloc(route_size);
    
    if (route == NULL) {
        perror("Route malloc failed");
        return;
    }
    
    strcpy(route, SECONDARY_STORAGE_ROOT);
    strncat(route, file_name, strlen(file_name));
    
    load_file_into_memory(route);
    
    free(route);
}


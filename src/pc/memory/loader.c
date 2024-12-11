// Libraries
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Config files
#include "../../../config/memory_globals.h"



void create_load_process(char *file_name) { 
    
    size_t route_size = strlen(SECONDARY_STORAGE_ROOT) + strlen(file_name) + 1; 

    char *route = malloc(route_size);

    if (route == NULL) {
        perror("malloc failed");
        return;
    }

    strcpy(route, SECONDARY_STORAGE_ROOT);
    strncat(route, file_name, strlen(file_name));
    puts(route);

    free(route);
}

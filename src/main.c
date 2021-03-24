#include "../include/utils.h"
#include "../include/sort_data.h"
#include "../include/sort_data_thread.h"
#include "../include/find_average_salary.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Too few arguments");
        return TOO_FEW_ARGUMENTS;
    }

    worker_t* workers;
    size_t size = 0;
    workers = gather_info(argv[1], &size);

    if (workers == NULL) {
        return CANNOT_GET_INFO_FROM_FILE;
    }

   
    main_list_t * head = NULL;
        
    for(size_t i = 0; i < size; i++) {
        head = add_elem_to_main_structure(workers[i], head);
    }
    
    if (strcmp(argv[2], "1") == 0)
    parallel_prog(head);
    if (strcmp(argv[2], "1") == 1)
    find_average_salary(head);
    sleep(1);
   

    free(workers);  // по логике она наверно в памяти должна оставаться
    return NO_ERROR;
}
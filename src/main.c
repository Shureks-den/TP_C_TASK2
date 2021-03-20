#include "../include/collect_data.h"
#include "../include/sort_data.h"
#include "../include/find_average_salary.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("Too few arguments");
        return -1;
    }
    worker_t* workers;
    size_t size = 0;
    workers = gather_info(argv[1], &size);
    //print_info(workers, &size);
    main_list_t * head = NULL;
    head = initialise_main_list(workers[0]);
    for(size_t i = 1; i < size; i++) {
        head = add_elem_to_main_structure(workers[i], head);
    }
    print_position_structure(head);
    find_average_salary(head);
    clear_position_structure(head);
    free(workers);  // по логике она наверно в памяти должна оставаться
    return 0;
}
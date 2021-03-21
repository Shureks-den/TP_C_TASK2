#include "../include/utils.h"
#include "../include/sort_data.h"
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
    head = initialise_main_list(workers[0]);
    if (head == NULL) {
        return CANNOT_BUILD_LIST_STRUCTURE;
    }
    for(size_t i = 1; i < size; i++) {
        head = add_elem_to_main_structure(workers[i], head);
    }

    if (head == NULL) {
        return ADDING_ERROR;
    }

    if (print_info(workers, &size)) {
        return CANNOT_PRINT_INFO_FROM_ARRAY;
    }
    if (print_position_structure(head)) {
        return CANNOT_PRINT_INFO_FROM_LIST_STRUCTURE;
    }

    if (find_average_salary(head)) {
        return ERROR_IN_BUILDING_AVERAGE_SALARY_MODEL;
    }
    if (clear_position_structure(head)) {
        return ERROR_IN_DELETING_LIST_STRUCTURE;
    }

    free(workers);  // по логике она наверно в памяти должна оставаться
    return NO_ERROR;
}
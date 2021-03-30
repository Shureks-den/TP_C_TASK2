#include "utils.h"
#include "sort_data.h"
#include "find_average_salary.h"
#include "find_average_salary_par.h"

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
        head = add_elem_to_main_structure(workers + i, head);
    }

    size_t data_size = 0;
    count_t* salary_data = find_average_salary(head, &data_size);
    print_average_salary(salary_data, &data_size);

    free(salary_data);
    clear_position_structure(head);
    free(workers);  // по логике она наверно в памяти должна оставаться
    return NO_ERROR;
}
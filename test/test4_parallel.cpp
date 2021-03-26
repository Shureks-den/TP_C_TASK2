#include <iostream>
#include "gtest/gtest.h"

extern "C" {
    #include "../include/utils.h"
    #include "../include/sort_data.h"
    #include "../include/find_average_salary_par.h"
}

TEST(finding_average_salary, test_salary) {
    worker_t* workers = NULL;
    size_t size = 0;
    char filename[] = "../workers_BIG.txt";
    workers = gather_info(filename, &size);
    
    main_list_t* head = NULL;
    head = initialise_main_list(workers[0]);
   
    for(size_t i = 1; i < size; ++i) {
        head = add_elem_to_main_structure(workers[i], head);
    }

    find_average_salary_parallel(head, sysconf(_SC_NPROCESSORS_ONLN));

    clear_position_structure(head);
    free(workers);
}
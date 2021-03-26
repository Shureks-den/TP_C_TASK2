#include <iostream>
#include <fstream>
#include "gtest/gtest.h"

extern "C" {
    #include "../include/utils.h"
    #include "../include/sort_data.h"
    #include "../include/find_average_salary.h"
}

TEST(finding_average_salary, test_salary) {
    worker_t* workers = NULL;
    size_t size = 0;
    char filename[] = "../workers_BIG.txt";
    workers = gather_info(filename, &size);
    
    main_list_t* head = NULL;
    
    for(size_t i = 0; i < size; ++i) {
        head = add_elem_to_main_structure(workers[i], head);
    }
    
    find_average_salary(head);
    clear_position_structure(head);
    free(workers);
}
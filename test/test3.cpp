#include <iostream>
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
    head = initialise_main_list(workers[0]);
   
    for(size_t i = 1; i < size; ++i) {
        head = add_elem_to_main_structure(workers[i], head);
    }

    ASSERT_EQ(find_average_salary(head), NO_ERROR);

    count_t* data_sort = NULL;
    ASSERT_EQ(print_average_salary(data_sort), CANNOT_PRINT_INFO_FROM_LIST_STRUCTURE);
    data_sort = (count_t*)malloc(sizeof(data_t));
    data_sort->experience = 2;
    data_sort->num_of_workers = 3;
    snprintf(data_sort->position, 23, "%s", "Somedata");
    data_sort->sum_salary = 1000;
    ASSERT_NE(print_average_salary(data_sort), 0);

    clear_position_structure(head);
    head = NULL;
    ASSERT_EQ(find_average_salary(head), ERROR_IN_BUILDING_AVERAGE_SALARY_MODEL);

    free(workers);
}
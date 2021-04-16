#include <iostream>
#include "gtest/gtest.h"

extern "C" {
    #include "utils.h"
    #include "sort_data.h"
    #include "find_average_salary.h"
}

TEST(finding_average_salary, test_salary) {
    worker_t* workers = NULL;
    size_t size = 0;
    char filename[] = "../workers_BIG.txt";
    workers = gather_info(filename, &size);
    
    main_list_t* head = NULL;
   
    for(size_t i = 0; i < size; ++i) {
        head = add_elem_to_main_structure(workers + i, head);
    }

    size_t i = 0;
    ASSERT_NE(find_average_salary(head, &i), nullptr);

    count_t* data_sort = NULL;
    ASSERT_EQ(print_average_salary(data_sort, 0), CANNOT_PRINT_INFO_FROM_LIST_STRUCTURE);
    data_sort = (count_t*)malloc(sizeof(data_t));
    data_sort->experience = 2;
    data_sort->num_of_workers = 3;
    snprintf(data_sort->position, 23, "%s", "Somedata");
    data_sort->sum_salary = 1000;
    i = 1;
    ASSERT_EQ(print_average_salary(data_sort, &i), NO_ERROR);

    clear_position_structure(head);
    head = NULL;
    ASSERT_EQ(find_average_salary(head, 0), nullptr);

    free(workers);
}
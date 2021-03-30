#include <iostream>
#include "gtest/gtest.h"

extern "C" {
    #include "utils.h"
    #include "sort_data.h"
    #include "find_average_salary_par.h"
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

    ASSERT_EQ(find_average_salary(head), NO_ERROR);

    position_list_t* position = NULL;


    clear_position_structure(head);
    head = NULL;
    ASSERT_EQ(find_average_salary(head), ERROR_IN_BUILDING_AVERAGE_SALARY_MODEL);

    clear_position_structure(head);
    free(workers);
}


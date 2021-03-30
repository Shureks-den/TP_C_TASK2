#include <iostream>
#include "gtest/gtest.h"

extern "C" {
    #include "utils.h"
    #include "sort_data.h"
    #include "find_average_salary_par.h"
}

TEST(finding_average_salary, test_salary) {  //  т.к тесты показывают время выполнения, данный тест вычисляет сколько времени займет
    worker_t* workers = NULL;               // выполнение параллельного алгоритма, от начала до конца
    size_t size = 0;
    char filename[] = "../workers_BIG.txt";
    workers = gather_info(filename, &size);
    
    main_list_t* head = NULL;
   
    for(size_t i = 0; i < size; ++i) {
        head = add_elem_to_main_structure(workers + i, head);
    }

    size_t data_size = 0;
    count_t* salary_data = find_average_salary(head, &data_size);
    print_average_salary(salary_data, &data_size);

    free(salary_data);
    clear_position_structure(head);
    free(workers);
}
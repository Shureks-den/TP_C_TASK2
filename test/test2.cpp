#include <iostream>
#include "gtest/gtest.h"

extern "C" {
    #include "utils.h"
    #include "sort_data.h"
}

TEST(forming_a_structure, making_a_list) {
    worker_t* workers = NULL;
    size_t size = 0;
    char filename[] = "../workers_BIG.txt";
    workers = gather_info(filename, &size);
    
    main_list_t* head = NULL;

    for(size_t i = 0; i < size; ++i) {
        head = add_elem_to_main_structure(workers + i, head);
        ASSERT_NE(head, nullptr);
    }

    ASSERT_EQ(clear_position_structure(head), NO_ERROR);
    head = NULL;
    head = add_elem_to_main_structure(workers, head);
    ASSERT_NE(head, nullptr);
    ASSERT_EQ(print_position_structure(head), NO_ERROR);
    
    free(workers);
}
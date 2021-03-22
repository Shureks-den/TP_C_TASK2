#include <iostream>
#include "gtest/gtest.h"

extern "C" {
    #include "../include/utils.h"
    #include "../include/sort_data.h"
}

TEST(forming_a_structure, making_a_list) {
    worker_t* workers = NULL;
    size_t size = 0;
    char filename[] = "../workers.txt";
    workers = gather_info(filename, &size);
    
    main_list_t* head = NULL;
    head = initialise_main_list(workers[0]);
    ASSERT_NE(head, nullptr);

    for(size_t i = 1; i < size; ++i) {
        head = add_elem_to_main_structure(workers[i], head);
        ASSERT_NE(head, nullptr);
    }

    position_list_t* worker = NULL;  // subfunction testing
    worker = insert_worker(NULL, workers[0]);
    ASSERT_EQ(worker, nullptr);

    worker = copy_data(NULL, NULL, workers[1]);
    ASSERT_NE(worker, nullptr);

    worker = copy_data(worker, NULL, workers[2]);
    ASSERT_NE(worker, nullptr);

    worker = copy_data(NULL, worker, workers[2]);
    ASSERT_NE(worker, nullptr);

    worker = insert_worker(worker, workers[0]); 
    ASSERT_NE(worker, nullptr);

    ASSERT_NE(print_data(*worker), 0);
    ASSERT_EQ(print_position_structure(head), NO_ERROR);

    ASSERT_EQ(clear_position_structure(head), NO_ERROR);
    head = NULL;
    head = add_elem_to_main_structure(workers[0], head);
    ASSERT_EQ(head, nullptr);
    ASSERT_NE(print_position_structure(head), NO_ERROR);
    
    free(workers);
}
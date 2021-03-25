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

    FILE* stream = freopen("got.txt", "w", stdout);
    ASSERT_NE(stream, nullptr);
    find_average_salary(head);
    fclose(stdout);

    std::ifstream t("got.txt");
    std::string got;
    std::string buff;
    while (t) {
        getline(t, buff);
        got += buff;
    }


    std::ifstream t2("../../expected.txt");
    std::string expected;
    while (t2) {
        getline(t2, buff);
        expected += buff;
    }

    t.close();
    t2.close();
    ASSERT_STREQ(got.c_str(), expected.c_str());

    clear_position_structure(head);
    free(workers);
}
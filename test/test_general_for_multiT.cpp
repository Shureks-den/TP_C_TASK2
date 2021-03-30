#include <iostream>
#include <fstream>
#include "gtest/gtest.h"

extern "C" {
    #include "utils.h"
    #include "sort_data.h"
    #include "find_average_salary_par.h"
}

TEST(finding_average_salary, test_par_algorithm) {
    worker_t* workers = NULL;
    size_t size = 0;
    char filename[] = "../workers_BIG.txt";
    workers = gather_info(filename, &size);
    
    main_list_t* head = NULL;
    
    for(size_t i = 0; i < size; ++i) {
        head = add_elem_to_main_structure(workers + i, head);
    }

    FILE* stream = freopen("got_multi_threaded.txt", "w", stdout);
    ASSERT_NE(stream, nullptr);
    size_t salary_data_size = 0;
    count_t* data = find_average_salary(head, &salary_data_size);
    print_average_salary(data, &salary_data_size);
    fclose(stdout);

    std::ifstream t("got_multi_threaded.txt");
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
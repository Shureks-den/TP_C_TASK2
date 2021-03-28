#include <iostream>
#include <fstream>
#include "gtest/gtest.h"

extern "C" {
    #include "utils.h"
}

TEST(utils_functions_test, test_reading_from_file) {  // проверка чтения файлов, в том числе не сушествующих
    worker_t* workers;
    size_t size = 0;
    char filename[] = "../workers_BIG.txt";  // директория внутри билда
    workers = gather_info(filename, &size);
    ASSERT_NE(workers, nullptr);
    free(workers);

    size = 0;
    workers = gather_info("not_a_file_lol.txt", &size);
    ASSERT_EQ(workers, nullptr);
    ASSERT_EQ(size, 0);

    char new_filename[] = "../workers_BIG.txt";
    workers = gather_info(new_filename, &size);

    std::ifstream base("../../workers_BIG.txt");  // проверка работы size и realloc
    int i = 0;
    char *str = new char [1024];

    while (!base.eof()) {
        base.getline(str, 1024, '\n');
        i++;
    }
    delete str;
    base.close();

    ASSERT_NE(workers, nullptr);
    ASSERT_EQ(size, i);
    free(workers);
}

TEST(utils_functions_test, printing_all_info) {  // проверка печати информации
    worker_t* workers;
    size_t size = 0;
    char filename[] = "../workers.txt";
    workers = gather_info(filename, &size);
    ASSERT_EQ(print_info(workers, &size), NO_ERROR);
    free(workers);
    workers = NULL;
    ASSERT_EQ(print_info(workers, &size), CANNOT_PRINT_INFO_FROM_ARRAY);
}
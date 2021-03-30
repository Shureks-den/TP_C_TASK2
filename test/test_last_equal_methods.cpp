#include <iostream>
#include <fstream>
#include "gtest/gtest.h"


TEST(testing_algorithyms, equality) {   //  сравнение вывода двух файлов
    
    std::ifstream t("got_one_threaded.txt");
    std::string got;
    std::string buff;
    while (t) {
        getline(t, buff);
        got += buff;
    }
    std::cout << got;

    std::ifstream t2("got_multi_threaded.txt");
    std::string expected;
    while (t2) {
        getline(t2, buff);
        expected += buff;
    }
    std::cout << expected;

    t.close();
    t2.close();
    ASSERT_STREQ(got.c_str(), expected.c_str());

}
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BIGCOMPANY 10000  // ориентировочная цифра
#define GROW 1000  // коэффициент для realloc


typedef struct worker {
    char name[19];
    char surname[20];
    char position[26];
    char gender[7];
    short age;
    short experience;
    unsigned int salary;
} worker_t;

enum error_list {
    NO_ERROR = 0,
    TOO_FEW_ARGUMENTS = 1,
    CANNOT_GET_INFO_FROM_FILE = 2,
    CANNOT_BUILD_LIST_STRUCTURE = 3,
    ADDING_ERROR = 4,
    CANNOT_PRINT_INFO_FROM_ARRAY = 5,
    CANNOT_PRINT_INFO_FROM_LIST_STRUCTURE = 6,
    ERROR_IN_BUILDING_AVERAGE_SALARY_MODEL = 7,
    ERROR_IN_DELETING_LIST_STRUCTURE = 8,
    SNPRINTF_ERROR = 9,
};

worker_t* gather_info(const char source[], size_t* size);  // функция чтобы загрузить это чудо в память
int print_info(worker_t* workers, size_t* size);  // печать общей инфы(для дебага)


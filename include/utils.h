#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BIGCOMPANY 100000  // ориентировочная цифра
#define GROW 10000  // коэффициент для realloc
#define INFO_FOR_REPORT 3

typedef struct count {
    unsigned int sum_salary;
    short num_of_workers;
    short experience;
    char position[24];
} count_t;

typedef struct data {
    char position[26];
    short experience;
    unsigned int salary;
} data_t;

typedef struct position_list position_list_t;
struct position_list {
    data_t data;
    position_list_t* next;
};

typedef struct main_list main_list_t;
struct main_list {
    position_list_t* head;
    main_list_t* next_list;
};

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
    NODES_ERROR = 10,
    THREAD_ERROR = 11
};

worker_t* gather_info(const char source[], size_t* size);  // функция чтобы загрузить это чудо в память
int print_info(worker_t* const workers, size_t* const size);  // печать общей инфы(для дебага)

int print_average_salary(count_t* const data); // печать итоговой информации
int count_nodes(main_list_t* const head);

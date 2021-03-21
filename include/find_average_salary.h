#pragma once
#include "sort_data.h"


typedef struct count {
    unsigned int sum_salary;
    short num_of_workers;
    short experience;
    char position[24];
} count_t;

int find_average_salary(main_list_t* head);
int print_average_salary(count_t* data);
#pragma once
#include "utils.h"
#include "sort_data.h"
#include "find_average_salary.h"

#include <pthread.h>
#include <unistd.h>

#define unlikely(expr) __builtin_expect(!!(expr), 0)
#define likely(expr) __builtin_expect(!!(expr), 1)

typedef struct {
    position_list_t** nodes_pointer_array;
    int num;
} partition;

void* thread_routine(void *arg);
void find_average_salary_parallel(main_list_t* head);
int find_average_salary_in_node(position_list_t* position);
int count_nodes(main_list_t* head);
int print_average_salary(count_t* data);

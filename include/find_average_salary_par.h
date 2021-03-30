#pragma once
#include "sort_data.h"

#include <pthread.h>
#include <unistd.h>

count_t* find_average_salary(main_list_t* const head, size_t* data_size);

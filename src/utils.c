#include "../include/utils.h"
#include <stdbool.h>

worker_t* gather_info(const char source[], size_t* size) {
    FILE* database = NULL;
    char path[30] = "../";
    strcat(path, source);
    database = fopen(path, "r");
    if (database == NULL) {
        puts("Error openning the file");
        return NULL;
    }

    size_t i = *size;
    size_t company_size = BIGCOMPANY;

    worker_t* workers = malloc(sizeof(worker_t) * BIGCOMPANY);
    if (workers == NULL) {
        fclose(database);
        return NULL;
    }

    while (fscanf(database, "%18s%19s%6s%hd%u%25s%hd", workers[i].name, workers[i].surname, workers[i].gender, &workers[i].age, &workers[i].salary, workers[i].position, &workers[i].experience) > 0) {
        i++;

        if (i == company_size) {
            worker_t* tmp = realloc(workers, sizeof(worker_t) * (i + GROW));   // если сотрудников больше 10к
            if (tmp == NULL) {
                free(workers);
                fclose(database);
                return NULL;
            }
        company_size += GROW;
        workers = tmp;
        }
    }
    *size = i;
    fclose(database);
    return workers;
}

int print_info(worker_t* workers, size_t* size) {
    if (workers == NULL || size == NULL) {
        return CANNOT_PRINT_INFO_FROM_ARRAY;
    }
    for(size_t i = 0; i < *size; i++) {
        if (printf("Name : %s\nSurname : %s\nGender : %s\nAge : %hd\nSalary: %u\nPosition: %s\nWork Experience (years) : %hd\n\n", 
        workers[i].name, workers[i].surname, workers[i].gender, workers[i].age, workers[i].salary, workers[i].position, workers[i].experience) < 6) {
            return CANNOT_PRINT_INFO_FROM_ARRAY;
        }
    }
    return NO_ERROR;
}

int print_average_salary(count_t* data) {
    if (data == NULL) {
        return CANNOT_PRINT_INFO_FROM_LIST_STRUCTURE;
    }
    return printf("------------------------------------------------------------------\n"
    "For %s with %hi years of experience average salary is: %u\n", 
    data->position, data->experience, data->sum_salary/data->num_of_workers);
}

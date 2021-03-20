#include "../include/collect_data.h"
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
    worker_t* workers = malloc(sizeof(worker_t) * BIGCOMPANY);
    if (workers == NULL) {
        fclose(database);
        return NULL;
    }
    while (fscanf(database, "%s%s%s%hd%u%s%hd", workers[i].name, workers[i].surname, workers[i].gender, &workers[i].age, &workers[i].salary, workers[i].position, &workers[i].experience) > 0) {
        i++;
        if (i == BIGCOMPANY) {
            workers = realloc(workers, sizeof(worker_t) * (i + GROW));
        }
        if (workers == NULL) {
            fclose(database);
            return NULL;
        }
    }
    *size = i;
    fclose(database);
    return workers;
}

int print_info(worker_t* workers, size_t* size) {
    for(size_t i = 0; i < *size; i++) {
        printf("Name : %s\nSurname : %s\nGender : %s\nAge : %hd\nSalary: %u\nPosition: %s\nWork Experience (years) : %hd\n\n", 
        workers[i].name, workers[i].surname, workers[i].gender, workers[i].age, workers[i].salary, workers[i].position, workers[i].experience);
    }
    return 0;
}


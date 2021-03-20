#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BIGCOMPANY 10000
#define GROW 1000


typedef struct worker {  // оптимизировал как черт 0 байтов потеряно
    char name[19];
    char surname[20];
    char position[26];
    char gender[7];
    short age;
    short experience;
    unsigned int salary;
} worker_t;


worker_t* gather_info(const char source[], size_t* size);  // функция чтобы загрузить это чудо в память
int print_info(worker_t* workers, size_t* size);  // печать общей инфы(для дебага)


#include "../include/find_average_salary_par.h"

#define unlikely(expr) __builtin_expect(!!(expr), 0)
#define likely(expr) __builtin_expect(!!(expr), 1)

void* thread_routine(void *arg) {
    partition* data = (partition*) arg;

    for(int i = 0; i < data->num; i++) {
        find_average_salary_in_node(data->nodes_pointer_array[i]);
    }
    free(data);
    pthread_exit(0);
}

void find_average_salary_parallel(main_list_t* head) {
    main_list_t* q = head;
    long int NUM_THREADS = sysconf(_SC_NPROCESSORS_ONLN);

    int nodes = count_nodes(head);
    pthread_t threadIds[NUM_THREADS];

    position_list_t** nodes_pointer_array = malloc(sizeof(position_list_t*) * (nodes));  // максимальное количество в одном потоке
    for (int i = 0; i < nodes; i++) {
        nodes_pointer_array[i] = q->head;
        q = q->next_list;
    }

    partition** data = malloc(sizeof(partition*) * NUM_THREADS);
    int info_per_thread = nodes / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        data[i] = malloc(sizeof(partition));
        data[i]->num = info_per_thread;
        data[i]->nodes_pointer_array = nodes_pointer_array + i * info_per_thread;

        if (unlikely(i == NUM_THREADS - 1)) {  // не кратное число нодов потокам
            data[i]->num += nodes % NUM_THREADS;
        } 
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threadIds[i], NULL, thread_routine, (void*) data[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threadIds[i], NULL);
    }

    free(nodes_pointer_array);
    free(data);
}

int find_average_salary_in_node(position_list_t* position) {

    count_t* data_sort = NULL;
    data_sort = malloc(sizeof(data_t));

    data_sort->experience = position->data.experience;
    data_sort->sum_salary = 0;
    data_sort->num_of_workers = 0;
    if (unlikely(snprintf(data_sort->position, sizeof(data_sort->position), "%s", position->data.position) < 1)) {
        free(data_sort);
        return SNPRINTF_ERROR;
    }
    while (position != NULL) {
        if (data_sort->experience != position->data.experience) {
            if (unlikely(print_average_salary(data_sort) < 3)) {
                return ERROR_IN_BUILDING_AVERAGE_SALARY_MODEL;
            }
            data_sort->num_of_workers = 0;
            data_sort->sum_salary = 0;
            data_sort->experience = position->data.experience;
        }
        data_sort->sum_salary += position->data.salary;
        data_sort->num_of_workers ++;
        position = position->next;
            
    }
    print_average_salary(data_sort);
    free(data_sort);
    return 0;
}

int count_nodes(main_list_t* head) {
    main_list_t* q = head;
    int i = 0;
    while(q != NULL) {
        i++;
        q = q->next_list;
    }
    return i;
}

int print_average_salary(count_t* data) {
    if (unlikely(data == NULL)) {
        return CANNOT_PRINT_INFO_FROM_LIST_STRUCTURE;
    }
    return printf("------------------------------------------------------------------\n"
    "For %s with %hi years of experience average salary is: %u\n", 
    data->position, data->experience, data->sum_salary/data->num_of_workers);
}
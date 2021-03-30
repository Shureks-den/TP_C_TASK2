#include "find_average_salary_par.h"

#define unlikely(expr) __builtin_expect(!!(expr), 0)
#define likely(expr) __builtin_expect(!!(expr), 1)

typedef struct {
    position_list_t** nodes_pointer_array;  //  неотсортированные ноды
    int num;  //  сколько в поток передается нодов
    size_t *data_size;  //  массив количества стажей
    count_t** data_sort;  //  указатель на массив массивов отсортированных структур
} partition;

static count_t* find_average_salary_in_node(position_list_t* position, size_t* data_size) {
    if (position == NULL) {
        return NULL;
    }

    count_t* data_sort = NULL;
    data_sort = malloc(sizeof(count_t) * MAX_EXPERIENCE);

    if (data_sort == NULL) {
        return NULL;
    }
    size_t i = 0;

    data_sort[i].experience = position->data.experience;
    data_sort[i].sum_salary = 0;
    data_sort[i].num_of_workers = 0;
    if (unlikely(snprintf(data_sort[i].position, sizeof(data_sort[i].position), "%s", position->data.position) < 1)) {
        free(data_sort);
        return NULL;
    }

    while (position != NULL) {
        if (data_sort[i].experience != position->data.experience) {
            i++;
            data_sort[i].num_of_workers = 0;
            data_sort[i].sum_salary = 0;
            data_sort[i].experience = position->data.experience;
            if (unlikely(snprintf(data_sort[i].position, sizeof(data_sort[i].position), "%s", position->data.position) < 1)) {
                free(data_sort);
                return NULL;
            }
        }

        data_sort[i].sum_salary += position->data.salary;
        data_sort[i].num_of_workers++;
        position = position->next;
    }
    i++;
    *data_size = i;
    return data_sort;  // возвращаем указатель на массив
}

static void* thread_routine(void* arg) {
    if (unlikely(arg == NULL)) {
        pthread_exit(0);
    }
    partition* data = (partition*) arg;

    for(size_t i = 0; i < data->num; i++) {
        data->data_sort[i] = find_average_salary_in_node(data->nodes_pointer_array[i], &data->data_size[i]);
    }
    pthread_exit(0);
}

static void clear_mem(partition* data) {
    free(data->data_sort);
    free(data->data_size);
    free(data);
}

static count_t* merge_data_together(partition** data, int nodes, size_t* size) {  //  функция склеивания данные для отчета
    count_t* data_sort = NULL;
    long int NUM_THREADS = sysconf(_SC_NPROCESSORS_ONLN);

    data_sort = malloc(sizeof(count_t) * nodes * MAX_EXPERIENCE);

    size_t move = 0;
    for (size_t i = 0; i < NUM_THREADS; i++) {
        for (size_t j = 0; j < data[i]->num; j++) {
            memcpy(data_sort + move, data[i]->data_sort[j], sizeof(count_t) * data[i]->data_size[j]);
            move += data[i]->data_size[j];
            free(data[i]->data_sort[j]);
        }
        clear_mem(data[i]);
    }

    *size = move;
    return data_sort;
}

count_t*  find_average_salary(main_list_t* const head, size_t* size) {
    if (head == NULL) {
        return NULL;
    }
    main_list_t* q = head;
    long int NUM_THREADS = sysconf(_SC_NPROCESSORS_ONLN);

    int nodes = count_nodes(head);
    pthread_t threadIds[NUM_THREADS];

    position_list_t** nodes_pointer_array = malloc(sizeof(position_list_t*) * (nodes));  // максимальное количество в одном потоке
    if (nodes_pointer_array == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < nodes; i++) {
        nodes_pointer_array[i] = q->head;
        q = q->next_list;
    }

    partition** data = malloc(sizeof(partition*) * NUM_THREADS);
    if (data == NULL) {
        free(nodes_pointer_array);
        return NULL;
    }
    int info_per_thread = nodes / NUM_THREADS;

    for (size_t i = 0; i < NUM_THREADS; i++) {
        data[i] = malloc(sizeof(partition));
        if (data[i] == NULL) {
            free(nodes_pointer_array);
            free(data);
            return NULL;
        }
        data[i]->data_sort = malloc(sizeof(data_t*)*(MAX_EXPERIENCE));
        if (data[i]->data_sort == NULL) {
            free(nodes_pointer_array);
            free(data[i]);
            free(data);
            return NULL;
        }
        data[i]->data_size = malloc(sizeof(size_t)*MAX_EXPERIENCE);
        if (data[i]->data_size == NULL) {
            free(nodes_pointer_array);
            free(data[i]->data_sort);
            free(data[i]);
            free(data);
            return NULL;
        }
        data[i]->num = info_per_thread;
        data[i]->nodes_pointer_array = nodes_pointer_array + i * info_per_thread;

        if (unlikely(i == NUM_THREADS - 1)) {  // не кратное число нодов потокам
            data[i]->num += nodes % NUM_THREADS;
        } 
    }

    for (size_t i = 0; i < NUM_THREADS; i++) {
        int errflag = pthread_create(&threadIds[i], NULL, thread_routine, (void*) data[i]);
        if (unlikely(errflag != 0)) {
            for (; i < NUM_THREADS; ++i) {
                clear_mem(data[i]);
            }
            free(nodes_pointer_array);
            free(data);
            return NULL;
        }
    }

    for (size_t i = 0; i < NUM_THREADS; i++) {
        int errflag = pthread_join(threadIds[i], NULL);
        if (unlikely(errflag != 0)) {
            for (; i < NUM_THREADS; ++i) {
                clear_mem(data[i]);
            }
            free(nodes_pointer_array);
            free(data);
            return NULL;
        }
    }
    
    count_t* data_sort = merge_data_together(data, nodes, size);
    free(nodes_pointer_array);
    free(data);
    return data_sort;
}




#include "find_average_salary.h"

count_t* find_average_salary(main_list_t* const head, size_t* data_size) {
    if (head == NULL) {
        return NULL;
    }
    
    int nodes_num = count_nodes(head);
    main_list_t* q = head;
    count_t* data_sort = NULL;

    data_sort = malloc(sizeof(count_t) * nodes_num * MAX_EXPERIENCE);
    if (data_sort == NULL) {
        return NULL;
    }

    size_t i = 0;
    while (q != NULL) {
        position_list_t* p = q->head;
 
        data_sort[i].experience = p->data.experience;
        data_sort[i].sum_salary = 0;
        data_sort[i].num_of_workers = 0;
        if (snprintf(data_sort[i].position, sizeof(data_sort[i].position), "%s", p->data.position) < 1) {
            free(data_sort);
            return NULL;
        }

        while (p != NULL) {
            if (data_sort[i].experience != p->data.experience) {
                i++;
                data_sort[i].num_of_workers = 0;
                data_sort[i].sum_salary = 0;
                data_sort[i].experience = p->data.experience;
                if (snprintf(data_sort[i].position, sizeof(data_sort[i].position), "%s", p->data.position) < 1) {
                    free(data_sort);
                    return NULL;
                }
            }
            data_sort[i].sum_salary += p->data.salary;
            data_sort[i].num_of_workers ++;
            p = p->next;
        }
        i++;
        q = q->next_list;
        
    }
    *data_size = i;
    return data_sort;
}

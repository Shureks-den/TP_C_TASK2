#include "../include/find_average_salary.h"

int find_average_salary(main_list_t* head) {
    if (head == NULL) {
        return 1;
    }
    main_list_t* q = head;
    count_t* data_sort = NULL;
    data_sort = malloc(sizeof(data_t));

    while (q != NULL) {
        position_list_t* p = q->head;
 
        data_sort->experience = p->data.experience;
        data_sort->sum_salary = 0;
        data_sort->num_of_workers = 0;
        if (snprintf(data_sort->position, sizeof(p->data.position), "%s", p->data.position) < 1) {
            return -1;
        }

        while (p != NULL) {
            if (data_sort->experience != p->data.experience) {
                print_average_salary(data_sort);
                data_sort->num_of_workers = 0;
                data_sort->sum_salary = 0;
                data_sort->experience = p->data.experience;
            }
            data_sort->sum_salary += p->data.salary;
            data_sort->num_of_workers ++;
            p = p->next;
            
        }
        print_average_salary(data_sort);
        q = q->next_list;
        
    }
    free(data_sort);
    return 0;
}

int print_average_salary(count_t* data) {
    return printf("---------------\nFor %s with %u years of experience average salary is: %u\n", 
    data->position, data->experience, data->sum_salary/data->num_of_workers);
}
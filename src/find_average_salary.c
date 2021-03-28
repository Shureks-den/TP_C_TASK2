#include "find_average_salary.h"

int find_average_salary(main_list_t* head) {
    if (head == NULL) {
        return ERROR_IN_BUILDING_AVERAGE_SALARY_MODEL;
    }
    main_list_t* q = head;
    count_t* data_sort = NULL;
    data_sort = malloc(sizeof(data_t));

    while (q != NULL) {
        position_list_t* p = q->head;
 
        data_sort->experience = p->data.experience;
        data_sort->sum_salary = 0;
        data_sort->num_of_workers = 0;
        if (snprintf(data_sort->position, sizeof(data_sort->position), "%s", p->data.position) < 1) {
            free(data_sort);
            return SNPRINTF_ERROR;
        }

        while (p != NULL) {
            if (data_sort->experience != p->data.experience) {
                if (print_average_salary(data_sort) < INFO_FOR_REPORT) {
                    free(data_sort);
                    return ERROR_IN_BUILDING_AVERAGE_SALARY_MODEL;
                }
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
    return NO_ERROR;
}

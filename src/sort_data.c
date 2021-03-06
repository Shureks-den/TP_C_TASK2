#include "sort_data.h"

static main_list_t* initialise_main_list(worker_t* const element) {
    if (element == NULL) {
        return NULL;
    }

    main_list_t* current = malloc(sizeof(main_list_t));
    if (current == NULL) {
        return NULL;
    }
    current->next_list = NULL;
    current->head = NULL;
    current->head = malloc(sizeof(position_list_t));

    if (current->head == NULL) {
        free(current);
        return NULL;
    }
    current->head->next = NULL;

    current->head->data.experience = element->experience;
    current->head->data.salary = element->salary;
    if (snprintf(current->head->data.position,  sizeof(element->position), "%s", element->position) < 0) {
        free(current->head);
        free(current);
        return NULL;
    }

    return current;
}

static position_list_t* copy_data(position_list_t* pre_current, position_list_t* current,  worker_t* const element) {
    if (element == NULL) {
        return NULL;
    }

    position_list_t* new_elem = malloc(sizeof(position_list_t));

    if (pre_current != NULL) {
        pre_current->next = new_elem;
    }
    new_elem->next = current;

    new_elem->data.experience = element->experience;
    new_elem->data.salary = element->salary;
    if (snprintf(new_elem->data.position, sizeof(element->position), "%s", element->position) < 0) {
        free(new_elem);
        return NULL;
    }

    return new_elem;
}

static position_list_t* insert_worker(position_list_t* head,  worker_t* const element) {
    if (head == NULL || element == NULL) {
        return NULL;
    }
    position_list_t* current = head;
    position_list_t* pre_current = current;

    if (head->data.experience > element->experience) {  // вставка в качестве первого
        head = copy_data(NULL, head, element);
        return head;
    }

    while (current != NULL) {
        if (current->data.experience > element->experience) {  // вставка в списке
            copy_data(pre_current, current, element);
            return head;
        }
        pre_current = current;
        current = current->next;
    }
    copy_data(pre_current, NULL, element);
    return head;
}

static int print_data(position_list_t* const get_data) {
    if (get_data == NULL) {
        return CANNOT_PRINT_INFO_FROM_LIST_STRUCTURE;
    }
    return printf("%s\n%hd\n%u\n\n", get_data->data.position, get_data->data.experience, get_data->data.salary);
}

main_list_t* add_elem_to_main_structure(worker_t* const element, main_list_t* head) {
    if (head == NULL) {
        head = initialise_main_list(element);
    }
    main_list_t* current = head;
    main_list_t* pre_current = head;

    while (current != NULL) {  // поиск по всем существующим узлам
        if (strcmp(current->head->data.position, element->position) == 0) {
            current->head = insert_worker(current->head, element);
            return head;
        }
        pre_current = current;
        current = current->next_list;
    }

    current =  initialise_main_list(element);  // вставка нового узла
    pre_current->next_list = current;
    return head;
}


int clear_position_structure(main_list_t* head) {
    if (head == NULL) {
        return CANNOT_PRINT_INFO_FROM_LIST_STRUCTURE;
    }
    main_list_t* clean_struct = head;

    while (head != NULL) {
        position_list_t* clean_list = head->head;
        while (head->head != NULL) {
            head->head = head->head->next;
            free(clean_list);
            clean_list = head->head;
        }

        head = head->next_list;
        free(clean_struct);
        clean_struct = head;
    }
    return NO_ERROR;
}


int print_position_structure(main_list_t* const head) {
    if (head == NULL) {
        return CANNOT_PRINT_INFO_FROM_LIST_STRUCTURE;
    }
    main_list_t* q = head;
    printf("----------------------\n");
    while (q != NULL) {
        position_list_t* p = q->head;
        while (p != NULL) {
            if (print_data(p) < 0) {
                return CANNOT_PRINT_INFO_FROM_LIST_STRUCTURE;
            }
            p = p->next;
        }
        q = q->next_list;
        printf("----------------------\n");
    }
    return NO_ERROR;
}

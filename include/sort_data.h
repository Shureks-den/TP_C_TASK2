#pragma once
#include "utils.h"

main_list_t* add_elem_to_main_structure(worker_t element, main_list_t* head);
main_list_t* initialise_main_list(worker_t element);
position_list_t* insert_worker(position_list_t* head, worker_t element);
position_list_t* copy_data(position_list_t* pre_current, position_list_t* current, worker_t element);
int clear_position_structure(main_list_t* head);
int print_position_structure(main_list_t* head);
int print_data(position_list_t get_data);

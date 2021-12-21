/*
 * Name, hw8.c, CS 24000, Fall 2018
 * Last updated October 18, 2018
 */

#include "hw8.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

/*
 * function that takes 2 string and an integer as parameter to generate a node
 * for a single linked list.pointer is set to NULL
 * return the single_list generated
 */

single_list *create_single(char *first_name, char *last_name, int input) {
  assert(first_name != NULL);
  assert(last_name != NULL);
  char *first = NULL;
  char *last = NULL;
  first = (char *)malloc(strlen(first_name) + 1);
  assert(first != NULL);
  strcpy(first, first_name);
  last = (char *)malloc(strlen(last_name) + 1);
  assert(last != NULL);
  strcpy(last, last_name);
  single_list *res = malloc(sizeof(struct single_list));
  assert(res != NULL);
  res->age = input;
  res->first_name = first;
  res->last_name = last;
  res->next_ptr = NULL;
  return res;
} /* create_single() */

/*
 * function that takes 2 string and an integer as parameter to generate a node
 * for a single linked list. pointers set to Null return the single_list
 * generated.
 */

double_list *create_double(char *first_name, char *last_name, int input) {
  assert(first_name != NULL);
  assert(last_name != NULL);
  assert(input >= 0);
  char* first = NULL;
  char* last = NULL;
  first  = malloc(strlen(first_name) + 1);
  assert(first != NULL);
  strcpy(first, first_name);
  last = malloc(strlen(last_name) + 1);
  assert(last != NULL);
  strcpy(last, last_name);
  double_list *res = malloc(sizeof(struct double_list));
  assert(res != NULL);
  res->first_name = first;
  res->last_name = last;
  res->age = input;
  res->next_ptr = NULL;
  res->prev_ptr = NULL;
  return res;
} /* create_double() */

/*
 * append the node in 2nd parameter to the 1st. The orginal nodes follow the
 * 1st parameter will be append to the second
 */

void append_single(single_list *first, single_list *last) {
  assert(first != NULL);
  assert(last != NULL);
  assert(last->next_ptr == NULL);
  single_list *buffer = first->next_ptr;
  first->next_ptr = last;
  last->next_ptr = buffer;
} /* append_single() */

/*
 * append the node in 2nd parameter to the 1st. The orginal nodes follow
 * the 1st parameter will be append to the second
 */

void append_double(double_list *first, double_list *last) {
  assert(first != NULL);
  assert(last != NULL);
  assert(last->next_ptr == NULL);
  double_list *buffer = NULL;
  buffer = first->next_ptr;
  if (buffer != NULL) {
    buffer->prev_ptr = last;
  }
  first->next_ptr = last;
  last->prev_ptr = first;
  last->next_ptr = buffer;
} /* append_double() */

/*
 *
 */

double_list *single_to_double(single_list *input) {
  if (input == NULL) {
    return NULL;
  }
  double_list *buffer1 = NULL;
  double_list *buffer2 = NULL;
  buffer1 = create_double(input->first_name, input->last_name, input->age);
  buffer2 = create_double(input->next_ptr->first_name,
    input->next_ptr->last_name, input->next_ptr->age);
  append_double(buffer1, buffer2);
  double_list* res = buffer1;
  input = input->next_ptr;
  while (input->next_ptr != NULL) {
    buffer1 = buffer2;
    buffer2 = create_double(input->next_ptr->first_name,
      input->next_ptr->last_name,input->next_ptr->age);
    input = input->next_ptr;
    append_double(buffer1, buffer2);
  }
  return res;
} /* single_to_double() */

/*
 * delete a single node
 */

void delete_single(single_list *input) {
  assert(input != NULL);
  free(input->first_name);
  free(input->last_name);
  free(input);
  input->first_name = NULL;
  input->last_name = NULL;
  input = NULL;
} /* delete_single() */

/*
 * delete a double node 
 */

void delete_double(double_list *input) {
  assert(input != NULL);
  free(input->first_name);
  free(input->last_name);
  free(input);
  input->first_name = NULL;
  input->last_name = NULL;
  input = NULL;
} /* delete_double() */

/*
 *Delete the single list from the node passed in parameter
 */

void delete_single_list(single_list *input) {
  if(input == NULL){
    return;
  }
  single_list* buffer;
  while (input->next_ptr != NULL){
    buffer = input;
    input = input->next_ptr;
    delete_single(buffer);
  }
  delete_single(input);
} /* delete_single_list() */

/*
 * Delete the double list from the node passed in parameter
 */

void delete_double_list(double_list *input) {
  if(input == NULL){
    return;
  }
  double_list *buffer;
  while (input->next_ptr != NULL){
    buffer = input;
    input = input->next_ptr;
    delete_double(buffer);
  }
  delete_double(input);
} /*delete_double_list() */
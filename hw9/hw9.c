//
// Created by ynot on 2018/10/31.
//

/*
 * Name, hw9.c, CS 24000, Fall 2018
 * Last updated October 25, 2018
 */

#include "hw9.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

/*
 * The function that creates a node for double list and set the value pointed
 * to by the first argument to the new node 
 */
void create_double(double_list **prev, char *first_name,
  char *last_name, int input) {
  assert(prev != NULL);
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
  *prev = res;
  res->first_name = first;
  res->last_name = last;
  res->age = input;
  res->next_ptr = NULL;
  res->prev_ptr = NULL;
} /* create_double() */

/*
 * Append the double list node passed in 2nd arguement to the 1st arguement
 */

void append_double(double_list **prev, double_list *input) {
  assert(prev != NULL);
  assert(input != NULL);
  assert(input->next_ptr == NULL);
  assert(input->prev_ptr == NULL);
  if (*prev != NULL) {
    if((*prev)->next_ptr != NULL) {
      double_list *buffer = (*prev)->next_ptr;
      input->prev_ptr = (*prev);
      input->next_ptr = buffer;
      buffer->prev_ptr = input;
      (*prev)->next_ptr = input;
    }
    input->prev_ptr = *prev;
    (*prev)->next_ptr = input;
    *prev = input;
  }
  *prev = input;
}/* append_double() */

/*
 * Insert the node passed by second arguement to the double list which the 1st
 * arguement points to
 */

void insert_in_order(double_list **prev, double_list *input) {
  if (*prev == NULL) {
    *prev = input;
    return;
  }
  double_list *buffer = *prev;
  while ((buffer->prev_ptr) != NULL) {
    buffer = buffer->prev_ptr;
  }
  double_list* head = buffer;
  if (strcmp(input->last_name, head->last_name) < 0) {
    input->next_ptr = head;
    head->prev_ptr = input;
    *prev = input;
    return;
  }
  if (strcmp(head->last_name, input->last_name) == 0) {
    if (strcmp(head->first_name, input->first_name) > 0) {
      input->next_ptr = head;
      head->prev_ptr = input;
      *prev = input;
      return;
    }
  }
  while (strcmp(head->last_name, input->last_name) <= 0) {
    if (strcmp(head->last_name, input->last_name) == 0) {
      if (strcmp(head->first_name, input->first_name) > 0)  {
        double_list *temp = head->prev_ptr;
        append_double((&temp), input);
        *prev = input;
        return;
      }
    }
    if (head->next_ptr == NULL) {
      append_double(&head, input);
      *prev = input;
      return;
    }
    if(strcmp(head->next_ptr->last_name, input->last_name) > 0) {
      append_double(&head, input);
      *prev = input;
      return;
    }
    head = head->next_ptr;
  }
}/* inser_double() */

/*
 * remove the node passed in 2nd arguement and adjust the value pointed by
 * the first arguement arcordingly
 */

void remove_double(double_list **prev, double_list *input) {
  assert(prev != NULL);
  assert(input != NULL);
  if ((input->prev_ptr == NULL) &&
    (input->next_ptr == NULL)) {
    *prev = NULL;
    return;
  }
  else if (input->prev_ptr == NULL) {
    *prev = input->next_ptr;
    input->next_ptr->prev_ptr = NULL;
    input->next_ptr = NULL;
    return;
  }
  else {
    *prev = input->prev_ptr;
    if (input->next_ptr != NULL) {
      double_list *buffer1 = input->prev_ptr;
      double_list *buffer2 = input->next_ptr;
      buffer1->next_ptr = buffer2;
      buffer2->prev_ptr = buffer1;
      input->next_ptr = NULL;
      input->prev_ptr = NULL;
      return;
    }
    input->prev_ptr->next_ptr = NULL;
    input->next_ptr = NULL;
    input->prev_ptr = NULL;
    return;
  }
}/* remove_double() */

/*
 * Delete the value pointed to by the arguement
 */

void delete_double(double_list **input) {
  assert(input != NULL);
  assert(*input != NULL);
  assert((*input)->prev_ptr == NULL);
  assert((*input)->next_ptr == NULL);
  free((*input)->last_name);
  free((*input)->first_name);
  (*input)->last_name = NULL;
  (*input)->first_name = NULL;
  free(*input);
  *input = NULL;
}/* delete_double() */

/*
 * Delete all elements of the double list pointed to by the arguement
 */

void delete_double_list(double_list **input) {
  if((input == NULL) ||
    (*input == NULL)) {
    return;
  }
  double_list** buffer = input;
  double_list* buf = *input;
  remove_double(buffer, buf);
  delete_double(&buf);
  buf = *buffer;
  while (*buffer != NULL){
    remove_double(buffer, buf);
    delete_double(&buf);
    buf = *buffer;
  }
}/* delete_double_list() */

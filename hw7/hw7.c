/*
 * Name, hw7.c, CS 24000, Fall 2018
 * Last updated October 11, 2018
 */

#include "hw7.h"

#include <assert.h>
#include <stdlib.h>

/*
 * A method that returns the string passed in the 1st arguement based on
 * operataion.
 */

char *copy_string(char *val, int operation) {
  assert(operation == REVERSE ||
    operation == DUPLICATE);
  struct node *res = NULL;
  if (operation == DUPLICATE) {
    res = string_to_list(val, NO);
  }
  else {
    res = string_to_list(val, YES);
  }
  char *return_val = list_to_string(res);
  free_list(res);
  return return_val;
}

/*
 * The method that transfer a string into a linked list that represent the
 * string
 */

struct node *string_to_list(char *val, int reverse) {
  assert(val != NULL);
  assert(*val != '\0');
  assert(reverse == 1 ||
    reverse == 2);
  int count = 0;
  while (val[count] != '\0') {
    count++;
  }
  struct node* buffer = NULL;
  if (reverse == 1) {
    for (int i = 0; i < count; ++i) {
      buffer = prepend_char(buffer, val[i]);
    }
  }
  if (reverse == 2) {
    for (int i = 0; i < count; ++i) {
      buffer = append_char(buffer, val[i]);
    }
  }
  return buffer;
}

/*
 * Append a node(whose val is second arguement) to the linked list whose head
 * is the first arguement
 */

struct node *append_char(struct node *head, char val) {
  assert(val >= 32);
  struct node *va = malloc(sizeof(struct node));
  assert(va != NULL);
  va->next = NULL;
  va->val = val;
  if (head == NULL) {
    return va;
  }
  struct node* buf = NULL;
  buf = head;
  while (buf->next != NULL) {
    buf = buf->next;
  }
  buf->next = va;
  return head;
};

/*
 * A methods that add a new node to the head od the linked list whose original
 * head is the 1st arguement
 */

struct node *prepend_char(struct node *head, char val) {
  assert(val >= 32);
  struct node *res = malloc(sizeof(struct node));
  assert(res != NULL);
  res->val = val;
  res->next = head;
  return res;
}

/*
 * A method that transfer a linked list whose head is given in the 1st
 * arguement to a string
 */

char *list_to_string(struct node *input) {
  assert(input != NULL);
  int count = 1;
  struct node *buf = NULL;
  buf = input;
  while (buf->next != NULL) {
    count++;
    buf = buf->next;
  }
  char *res = (char *)malloc(count+1);
  assert(res != NULL);
  char *return_val = res;
  struct node *buffer = NULL;
  buffer = input;
  for (int i = 0; i < count; ++i) {
    *res = buffer->val;
    buffer = buffer->next;
    res++;
  }
  *res = '\0';
  return return_val;
}

/*
 * free the memory of linked list whose head is given in the parameter
 */

void free_list(struct node *input) {
  if(input == NULL) {
    return;
  }
  while (input->next != NULL) {
    struct node* buff = input;
    input = input->next;
    free(buff);
  }
  free(input);
}

/*
 * The function that connects 2 strings
 */

char *concat_strings(char *input_a, char* input_b) {
  assert(input_a != NULL);
  assert(*input_a!='\0');
  if(input_b == NULL ||
     *input_b == '\0') {
    struct node* a = NULL;
    a = string_to_list(input_a,NO);
    char* res = list_to_string(a);
    free_list(a);
    return res;
  }
  struct node* a = NULL;
  struct node* b = NULL;
  a = string_to_list(input_a, NO);
  b = string_to_list(input_b, NO);
  append_lists(a, b);
  char* res = list_to_string(a);
  free_list(a);
  return res;
}

/*
 * A method that connect to linked list whose heads are given in the parameters
 */

void append_lists(struct node *input_a, struct node *input_b) {
  assert(input_a != NULL);
  if (input_b == NULL){
    return;
  }
  while (input_a->next != NULL) {
    input_a = input_a->next;
  }
  input_a->next = input_b;
}
/**/

#include "hw10.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>

/*
 *  The function that creates a tree node struct based on the parameters and 
 *  return the pointer to the new tree struct created
 */

tree *tree_create(char *input1, char *input2, unsigned int id) {
  assert(input1 != NULL);
  assert(input2 != NULL);
  char* first = NULL;
  char* last = NULL;
  tree* res = malloc(sizeof(struct tree));
  assert(res != NULL);
  first  = malloc(strlen(input1) + 1);
  assert(first != NULL);
  strcpy(first, input1);
  last = malloc(strlen(input2) + 1);
  assert(last != NULL);
  strcpy(last, input2);
  res->name = first;
  res->title = last;
  res->id_number = id;
  res->left_ptr = NULL;
  res->right_ptr = NULL;
  return res;
} /* tree_create() */

/*
 * A recursive function that inserts the tree node passed in the second 
 * parameter into a sorted tree/subtree whose address of root is the 
 * first parameter.
 */

void tree_insert(tree **root, tree *input) {
  assert(root != NULL);
  assert(input != NULL);
  assert(input->right_ptr==NULL);
  assert(input->left_ptr==NULL);
  if (*root == NULL) {
    *root = input;
    return;
  }
  int buf = strcmp((*root)->name, input->name);
  if (buf >= 0) {
    tree_insert(&((*root)->left_ptr), input);
  }
  else {
    tree_insert(&((*root)->right_ptr), input);
  }
} /* tree_insert() */

/*
 * A recursive function that finds the tree node passed in the second 
 * parameter into an alphabetically sorted tree/subtree whose root is 
 * the first parameter.
 */

tree *tree_find(tree *input, char *name) {
  assert(name != NULL);
  if(input == NULL){
    return NULL;
  }
  int buf = strcmp(input->name, name);
  if (buf == 0 ) {
    tree* res = input;
    return res;
  }
  else if (buf > 0) {
    return tree_find(input->left_ptr, name);
  }
  else if(buf < 0) {
    return tree_find(input->right_ptr, name);
  }
  return NULL;
} /* tree_find() */

/*
 * An recursive function that deletes the entire tree whose address of root is
 * passed in the parameter
 */

void  tree_delete(tree **input) {
  assert(input != NULL);
  if (*input == NULL) {
    return;
  }
  tree *buf1 = (*input)->left_ptr;
  tree *buf2 = (*input)->right_ptr;
  tree_delete(&buf1);
  tree_delete(&buf2);
  free((*input)->name);
  (*input)->name = NULL;
  free((*input)->title);
  (*input)->title = NULL;
  (*input)->right_ptr = NULL;
  (*input)->left_ptr = NULL;
  free(*input);
  *input = NULL;
} /* tree_delete() */
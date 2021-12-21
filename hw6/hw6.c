/*
 * Name, hw6.c, CS 24000, Fall 2018
 * Last updated October 4, 2018
 */

#include "hw6.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>

human_t g_human_array[MAX_HUMANS];
unsigned int g_human_count = 0;

/*
 *The function that reads the Input and store them into g-human_array
 */

int read_humans(char *in_file) {

#define SCAN_INDEX (6)
#define CHAR_LENGTH (100)

  g_human_count = 0;
  assert(in_file != NULL);
  FILE *fp = NULL;
  fp = fopen(in_file, "r");
  if (fp == NULL) {
    return NON_READABLE_FILE;
  }
  while (g_human_count < MAX_HUMANS) {
    int count = 0;
    human_t buffer;
    char first[CHAR_LENGTH];
    char last[CHAR_LENGTH];
    char m_last[CHAR_LENGTH];
    char m_first[CHAR_LENGTH];
    char f_last[CHAR_LENGTH];
    char f_first[CHAR_LENGTH];
    count = fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%s\n",
      last, first, m_last, m_first, f_last, f_first);
    if (count == EOF) {
      break;
    }
    if (count != SCAN_INDEX) {
      fclose(fp);
      fp = NULL;
      return READ_BAD_RECORD;
    }
    if (strpbrk(f_first, ",") != NULL) {
      fclose(fp);
      fp = NULL;
      return READ_BAD_RECORD;
    }
    for (int i = 0; i < NAME_LENGTH - 1; i++) {
      buffer.last_name[i] = last[i];
      buffer.first_name[i] = first[i];
      buffer.mother_last[i] = m_last[i];
      buffer.mother_first[i] = m_first[i];
      buffer.father_last[i] = f_last[i];
      buffer.father_first[i] = f_first[i];
    }
    buffer.last_name[NAME_LENGTH - 1] = '\0';
    buffer.father_first[NAME_LENGTH - 1] = '\0';
    buffer.mother_first[NAME_LENGTH - 1] = '\0';
    buffer.father_last[NAME_LENGTH - 1] = '\0';
    buffer.mother_last[NAME_LENGTH - 1] = '\0';
    buffer.first_name[NAME_LENGTH - 1] = '\0';
    buffer.father_ptr = NULL;
    buffer.mother_ptr = NULL;
    buffer.child_ptr = NULL;
    buffer.sibling_ptr = NULL;
    g_human_array[g_human_count] = buffer;
    g_human_count++;
  }
  fclose(fp);
  fp = NULL;
  return g_human_count;
}

/*
 * Function that finds the Index of the children of the one whose name is given
 * by parameters. return 0 if none is found.
 */

int find_children(char* last_name, char* first_name) {
  assert (first_name != NULL);
  assert (last_name != NULL);
  for (int i = 0; i < g_human_count; i++) {
    if (((strcmp(last_name, g_human_array[i].mother_last) == 0) &&
      (strcmp(first_name, g_human_array[i].mother_first) == 0)) ||
      ((strcmp(last_name, g_human_array[i].father_last) == 0) &&
      (strcmp(first_name, g_human_array[i].father_first) == 0))) {
      return i;
    }
  }
  return 0;
}

/*
 * Function that finds the Index of the father of the one whose name is given
 * by parameters. return -1 if none is found.
 */

int find_father(char* f_last, char* f_first) {
  static int res = 0;
  res = -1;
  for (int i = 0; i < g_human_count; i++) {
    if ((strcmp(f_last, g_human_array[i].last_name) == 0) &&
      (strcmp(f_first, g_human_array[i].first_name) == 0)) {
      res = i;
    }
  }
  return res;
}

/*
 * similar to last one, find the Index of mother instead. return -1 if not
 * found.
 */

int find_mother(char* m_last, char* m_first) {
  static int res = 0;
  res = -1;
  for (int i = 0; i < g_human_count; i++) {
    if ((strcmp(m_last, g_human_array[i].last_name) == 0) &&
      (strcmp(m_first, g_human_array[i].first_name) == 0)) {
      return i;
    }
  }
  return res;
}

/*
 * Find the Index of sibling of the struct in 1st parameter. Second parameter is
 * the index of the struct passed in first parameter. return -1 if none is found
 */

int find_sibling(struct human_struct buf, int pos) {
  for (int i = pos + 1; i < g_human_count; ++i) {
    if(buf.mother_ptr!=NULL) {
      if ((g_human_array[i].father_ptr == buf.father_ptr) &&
        (g_human_array[i].mother_ptr == buf.mother_ptr)) {
        return i;
      }
    }
  }
  return -1;
}

/*
 * The function that use other functions to establish the family tree
 * represented by pointers
 */

void establish_family() {
  for (int i = 0; i < g_human_count; i++) {
    int a = find_children(g_human_array[i].last_name,
      g_human_array[i].first_name);
    if(a > 0) {
      g_human_array[i].child_ptr = &g_human_array[a];
    }
    int mother = 0;
    int father = 0;
    mother = -1;
    father = -1;
    mother = find_mother(g_human_array[i].mother_last,
       g_human_array[i].mother_first);
    father = find_father(g_human_array[i].father_last,
       g_human_array[i].father_first);
    if(father >= 0) {
      g_human_array[i].father_ptr = &g_human_array[father];
    }
    if(mother >= 0) {
      g_human_array[i].mother_ptr = &g_human_array[mother];
    }
  }
  for (int j = 0; j < g_human_count; ++j) {
    int sibling = 0;
    sibling = find_sibling(g_human_array[j], j);
    if(sibling > 0) {
      g_human_array[j].sibling_ptr = &g_human_array[sibling];
    }
  }
}


/*
 * Name, hw5.c, CS 24000, Fall 2018
 * Last updated September 27, 2018
 */
#include "hw5.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
human_t g_human_array[1000];
unsigned int g_human_count = 0;

int read_humans(char * in_file) {
  g_human_count = 0;
  assert(in_file!=NULL);
  FILE* fp = NULL;
  fp = fopen(in_file,"r");
  if (fp==NULL) {
    return NON_READABLE_FILE;
  }

  while (g_human_count<1000) {
    int count = 0;
    human_t buffer;
    char first[100];
    char last[100];
    char m_last[100];
    char m_first[100];
    char f_last[100];
    char f_first[100];
    count = fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%s\n",
                   last, first, m_last, m_first, f_last, f_first);
    if ( count == EOF) {
      break;
    }
      //printf("count is %d\n", count);
      if (count != 6) {
        fclose(fp);
        fp = NULL;
        return READ_BAD_RECORD;
      }
      //printf("count is QXXXXXXXXXXXX\n");
        if (strpbrk(f_first,",")!=NULL) {
          fclose(fp);
          fp = NULL;
          return READ_BAD_RECORD;
        }
      for (int i = 0; i < 9; i++) {
        buffer.last_name[i] = last[i];
        buffer.first_name[i] = first[i];
        buffer.mother_last[i] = m_last[i];
        buffer.mother_first[i] = m_first[i];
        buffer.father_last[i] = f_last[i];
        buffer.father_first[i] = f_first[i];
      } 
      buffer.last_name[9] = '\0';
      buffer.father_first[9] = '\0';
      buffer.mother_first[9] = '\0';
      buffer.father_last[9] = '\0';
      buffer.mother_last[9] = '\0';
      buffer.first_name[9] = '\0';
      g_human_array[g_human_count] = buffer;
      g_human_count++;
    }
    fclose(fp);
  return g_human_count;
}

int find_children(char* last_name,char* first_name, int* childreb_array){
  assert (first_name!=NULL);
  assert (last_name!=NULL);
  assert (childreb_array!=NULL);
  int count = 0 ;
  for (int i = 0 ; i < g_human_count ; i++){
    if ((strcmp(last_name, g_human_array[i].mother_last) == 0 &&
         strcmp(first_name, g_human_array[i].mother_first) == 0) ||
        (strcmp(last_name, g_human_array[i].father_last) == 0 &&
         strcmp(first_name, g_human_array[i].father_first) == 0)) {
      childreb_array[count] = i;
             count++;
    }
  }
  return count;
}

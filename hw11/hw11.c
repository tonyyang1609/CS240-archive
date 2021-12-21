/*
 * Name, hw12.c, CS 24000, Fall 2018
 * Last updated November 25, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include "object.h"
#include "graphics.h"

object *read_object(const char *filename) {
  FILE * fp1;
  fp1 = fopen(filename,"r");
  if (fp1 == NULL){
    return NULL;
  }
  object* buffer = malloc(sizeof(struct object));
  char in_name[20];
  int n_points = 0;
  int n_pol = 0;
  fscanf(fp1,"%s\n",in_name);
  fscanf(fp1,"%d %d\n",&n_points,&n_pol);
  printf("%s %d %d\n",in_name,n_points,n_pol);
  if(n_points <= 0 || n_pol <= 0) {
    return NULL;
  }
  buffer->num_points = n_points;
  buffer->num_polygons = n_pol;
  buffer->points = malloc(n_points* sizeof(point));
  printf("step1 \n");
  point* temp1 = buffer->points;
  int a = 0;
  for (int i = 0; i < n_points; ++i) {
    float f1;
    float f2;
    float f3;
    fscanf(fp1,"%d %f %f %f\n",&a,&f1,&f2,&f3);
    printf("%f %f %f \n",f1,f2,f3);
    temp1->arr[0] = f1;
    temp1->arr[1] = f2;
    temp1->arr[2] = f3;
    temp1++;
  }
  buffer->polygons = malloc(n_pol* sizeof(polygon));
  for (int i = 0; i < n_pol; ++i) {
    int n_point;
    char col[10];
    char name[10];
    fscanf(fp1,"%s %s %d ",name,col,&n_point);
    buffer->polygons->num_points = n_point;
    printf("%s %s %d \n",col,name,n_point);
    name_to_rgb(col,&(buffer->polygons->r),&(buffer->polygons->g),&(buffer->polygons->b));
    printf("%d %d %d \n",buffer->polygons->r,buffer->polygons->g,buffer->polygons->b);
    for (int j = 0; j < n_point; ++j) {
      int buf;
      if(j == n_point-1) {
        fscanf(fp1, "%d\n", &buf);
      } else{
        fscanf(fp1,"%d ",&buf);
      }
      int remain = n_points - a;
      point * temp =  buffer->points;
      if (remain == 0){
        for (int k = 1; k < buf; k++) {
          temp++;
        }
      } else{
        for (int k = 0; k < buf; k++) {
          temp++;
        }
      }
      buffer->polygons->point_arr = malloc(sizeof(point*)*(n_point+1));
      //printf("%f %f %f \n",temp->arr[0],temp->arr[1],temp->arr[2]);
      *(buffer->polygons->point_arr) = temp;
      (buffer->polygons->point_arr)++;
    }
    for (int l = 0; l < n_point; ++l) {
      (buffer->polygons->point_arr)--;
    }
  }
  printf("adssadasdasdsa\n");
  return buffer;
};
void free_object(object * input){
  printf("adssadasdasdsa\n");
};
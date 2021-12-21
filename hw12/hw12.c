/*
 * Name, hw12.c, CS 24000, Fall 2018
 * Last updated November 25, 2018
 */

#include "object.h"
#include "graphics.h"

#include <malloc_debug.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * The function will create a object based on the file whose name is passed in
 * the parameter.
 */

object *read_object(const char *filename) {
  FILE * fp1 = NULL;
  fp1 = fopen(filename, "r");
  if (fp1 == NULL) {
    return NULL;
  }
  object* buffer = malloc(sizeof(struct object));
  char in_name[20] = "";
  int n_points = 0;
  int n_pol = 0;
  fscanf(fp1, "%s\n", in_name);
  fscanf(fp1, "%d %d\n", &n_points, &n_pol);
  if ((n_points <= 0) ||
    (n_pol <= 0)) {
    return NULL;
  }
  buffer->num_points = n_points;
  buffer->num_polygons = n_pol;
  buffer->points = malloc(n_points * sizeof(point));
  buffer->polygons = malloc(n_pol * sizeof(polygon));
  int a = 0;
  for (int i = 0; i < n_points; ++i) {
    float f1 = 0.0;
    float f2 = 0.0;
    float f3 = 0.0;
    fscanf(fp1, "%d %f %f %f\n", &a, &f1, &f2, &f3);
    buffer->points[i].arr[0] = f1;
    buffer->points[i].arr[1] = f2;
    buffer->points[i].arr[2] = f3;
  }
  for (int i = 0; i < n_pol; ++i) {
    int n_point = 0;
    char col[10] = "";
    char name[10] = "";
    fscanf(fp1, "%s %s %d ", name,col, &n_point);
    buffer->polygons[i].num_points = n_point;
    name_to_rgb(col, &(buffer->polygons[i].r), &(buffer->polygons[i].g),
                &(buffer->polygons[i].b));
    buffer->polygons[i].point_arr = malloc(n_point * sizeof(point *));
    for (int j = 0; j < n_point; ++j) {
      int buf = 0;
      if (j == n_point - 1) {
        fscanf(fp1, "%d\n", &buf);
      }
      else {
        fscanf(fp1,"%d ",&buf);
      }
      int remain = 0;
      remain = n_points - a;
      point *temp = NULL;
      temp = buffer->points;
      if (remain == 0) {
        for (int k = 1; k < buf; k++) {
          temp++;
        }
      }
      else {
        for (int k = 0; k < buf; k++) {
          temp++;
        }
      }
      buffer->polygons[i].point_arr[j] = temp;
    }
  }
  fclose(fp1);
  fp1 = NULL;
  return buffer;
} /* read_object() */

/*
 * free the memory previous allocated with the object itself and its field
 */

void free_object(object *input) {
  free(input->points);
  input->points = NULL;
  for (int i = 0; i < input->num_polygons; ++i) {
    free(input->polygons[i].point_arr);
  }
  input->polygons->point_arr = NULL;
  free(input->polygons);
  input->polygons = NULL;
  free(input);
  input = NULL;
} /* free_object() */
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Matrix {
  double **matrix;
  int rows;
  int cols;
} matrix_t;

typedef struct facets {
  int *vertexes;
  int numbers_of_vertexes_in_facets;
} polygon_t;

struct data {
  int count_of_vertexes;
  int count_of_facets;
  matrix_t matrix_3d;
  polygon_t *polygons;
};

// back.c
struct data start(char *str);
void first_open(struct data *file, char *str1);
void second_open(struct data *file, char *str1);
int count_words(char *str);
void remove_matrix(struct data *file);

// afinne.c
double grad_to_rad(double grad);
matrix_t create_matrix(int rows, int columns);
matrix_t mult_matrix(matrix_t *A, matrix_t *B);
void rotation_x(matrix_t *A, double angle);
void rotation_y(matrix_t *A, double angle);
void rotation_z(matrix_t *A, double angle);
void move_x(matrix_t *A, double a);
void move_y(matrix_t *A, double a);
void move_z(matrix_t *A, double a);
void scale_x(matrix_t *A, double k);
void scale_y(matrix_t *A, double k);
void scale_z(matrix_t *A, double k);
void scale_xyz(matrix_t *A, double k);

// func for test
int s21_create_matrix(int rows, int columns, matrix_t *result);
int s21_eq_matrix(matrix_t *a, matrix_t *b);
struct data s21_create_data(int vertexes, int facets);
void s21_remove_polygon(polygon_t *A);
polygon_t s21_create_polygon(int size);

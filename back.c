#include "back.h"
#include <stdint.h>
#define V_CONDITION line_buf[0] == 'v' && line_buf[1] == ' '
#define F_CONDITION line_buf[0] == 'f' && line_buf[1] == ' '

struct data start(char *str) {
  struct data file = {0};
  if (str == NULL) {
    printf("EMPTY\n");
  } else {
    first_open(&file, str);
    second_open(&file, str);
  }
  return file;
}

void first_open(struct data *file, char *str1) {
  FILE *fp = fopen(str1, "r");
  size_t line_buf_size = 0;
  if (fp == NULL) {
    perror("Ошибка открытия файла");
  } else {
    char *line_buf = NULL;
    getline(&line_buf, &line_buf_size, fp);
    if (V_CONDITION)
      file->count_of_vertexes++;
    if (line_buf[0] == 'f')
      file->count_of_facets++;
    while (getline(&line_buf, &line_buf_size, fp) != -1) {
      if (V_CONDITION)
        file->count_of_vertexes++;
      if (line_buf[0] == 'f')
        file->count_of_facets++;
    }
    if (line_buf) {
      free(line_buf);
    }
  }
  fclose(fp);
}

void second_open(struct data *file, char *str1) {
  file->matrix_3d.rows = file->count_of_vertexes;
  file->matrix_3d.cols = 3;
  if (file->count_of_vertexes > 0) {
    file->matrix_3d.matrix =
        (double **)calloc(file->matrix_3d.rows, sizeof(double *));
    for (register int i = 0; i < file->matrix_3d.rows; i++) {
      file->matrix_3d.matrix[i] = calloc(file->matrix_3d.cols, sizeof(double));
    }
  }
  FILE *fp = fopen(str1, "r");
  size_t line_buf_size = 0;
  char *line_buf = NULL;
  if (fp == NULL) {
    perror("Ошибка открытия файла");
  } else {
    register int i = 0, j = 0;
    if (file->count_of_facets > 0) {
      file->polygons =
          (polygon_t *)malloc(file->count_of_facets * sizeof(polygon_t));
    }
    while (getline(&line_buf, &line_buf_size, fp) != -1) {
      if (V_CONDITION) {
        sscanf(line_buf + 2, "%lg %lg %lg", &file->matrix_3d.matrix[i][0],
               &file->matrix_3d.matrix[i][1], &file->matrix_3d.matrix[i][2]);
        i++;
      } else if (F_CONDITION) {
        int s = 0, cnt = 0;
        int cnt_words = count_words(line_buf);
        if (cnt_words > 0) {
          file->polygons[j].numbers_of_vertexes_in_facets = cnt_words;
          file->polygons[j].vertexes = (int *)malloc(
              file->polygons[j].numbers_of_vertexes_in_facets * sizeof(int));
        }
        while (cnt != file->polygons[j].numbers_of_vertexes_in_facets) {
          if (line_buf[s] == ' ' && isdigit(line_buf[s + 1])) {
            sscanf(line_buf + s + 1, "%d", &file->polygons[j].vertexes[cnt]);
            cnt++;
          }
          s++;
        }
        j++;
      }
    }
    if (line_buf) {
      free(line_buf);
    }
  }
  fclose(fp);
}

int count_words(char *str) {
  register int cnt = 0;
  while (strlen(str)) {
    if (*str == ' ' && isdigit(*(str - 1)) && isdigit(*(str + 1))) {
      cnt++;
    }
    str++;
  }
  return cnt + 1;
}

// func for test

void remove_matrix(struct data *file) {
  for (register int i = 0; i < file->matrix_3d.rows; i++) {
    if (file->matrix_3d.matrix[i]) {
      free(file->matrix_3d.matrix[i]);
    }
  }
  if (file->matrix_3d.matrix) {
    free(file->matrix_3d.matrix);
  }
  file->matrix_3d.rows = 0;
  file->matrix_3d.cols = 0;
  for (register int j = 0; j < file->count_of_facets; j++) {
    if (file->polygons[j].vertexes)
      free(file->polygons[j].vertexes);
  }
  if (file->polygons)
    free(file->polygons);
  file->count_of_facets = 0;
  file->count_of_vertexes = 0;
}

int s21_eq_matrix(matrix_t *a, matrix_t *b) {
  int8_t result = 1;
  if ((a->rows != b->rows) || (a->cols != b->cols)) {
    result = 0;
  } else {
    register int i, j;
    for (i = 0; i < a->rows; i++) {
      for (j = 0; j < a->cols; j++) {
        double eq = a->matrix[i][j] - b->matrix[i][j];
        if (fabs(eq) > 0.001) {
          result = 0;
        }
      }
    }
  }
  return result;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int8_t flag = 0;
  result->rows = rows;
  result->cols = columns;
  result->matrix = (double **)calloc(rows, sizeof(double *));
  if (result->matrix != NULL) {
    for (register int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
    }
  }
  return flag;
}

polygon_t s21_create_polygon(int size) {
  polygon_t polygon;
  polygon.numbers_of_vertexes_in_facets = size;
  polygon.vertexes = (int *)calloc(size, sizeof(int));
  for (register int i = 0; i <= size; i++) {
    polygon.vertexes[i] = 0;
  }
  return polygon;
}

void s21_remove_polygon(polygon_t *A) {
  if (A != NULL) {
    if (A->vertexes != NULL) {
      free(A->vertexes);
    }
  }
}

struct data s21_create_data(int vertexes, int facets) {
  struct data obj;
  obj.count_of_vertexes = vertexes;
  obj.count_of_facets = facets;
  s21_create_matrix(vertexes, 3, &(obj.matrix_3d));
  obj.polygons = (polygon_t *)calloc(facets, sizeof(polygon_t));
  for (register int i = 0; i <= facets; i++) {
    obj.polygons[i] = s21_create_polygon(3);
  }
  return obj;
}

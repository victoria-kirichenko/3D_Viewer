#include <check.h>

#include "back.h"

char *file_name = "./obj_files/cube.obj";

START_TEST(data_1) {
  struct data exp;
  exp = s21_create_data(8, 12);
  exp.count_of_vertexes = 36;
  exp.matrix_3d.matrix[0][0] = 1.0;
  exp.matrix_3d.matrix[0][1] = -1.0;
  exp.matrix_3d.matrix[0][2] = -1.0;

  exp.matrix_3d.matrix[1][0] = 1.0;
  exp.matrix_3d.matrix[1][1] = -1.0;
  exp.matrix_3d.matrix[1][2] = 1.0;

  exp.matrix_3d.matrix[2][0] = -1.0;
  exp.matrix_3d.matrix[2][1] = -1.0;
  exp.matrix_3d.matrix[2][2] = 1.0;

  exp.matrix_3d.matrix[3][0] = -1.0;
  exp.matrix_3d.matrix[3][1] = -1.0;
  exp.matrix_3d.matrix[3][2] = -1.0;

  exp.matrix_3d.matrix[4][0] = 1.0;
  exp.matrix_3d.matrix[4][1] = 1.0;
  exp.matrix_3d.matrix[4][2] = -0.999999;

  exp.matrix_3d.matrix[5][0] = 0.999999;
  exp.matrix_3d.matrix[5][1] = 1.0;
  exp.matrix_3d.matrix[5][2] = 1.000001;

  exp.matrix_3d.matrix[6][0] = -1.0;
  exp.matrix_3d.matrix[6][1] = 1.0;
  exp.matrix_3d.matrix[6][2] = 1.0;

  exp.matrix_3d.matrix[7][0] = -1.0;
  exp.matrix_3d.matrix[7][1] = 1.0;
  exp.matrix_3d.matrix[7][2] = -1.0;

  exp.polygons[0].vertexes[0] = 2;
  exp.polygons[0].vertexes[1] = 3;
  exp.polygons[0].vertexes[2] = 4;

  exp.polygons[1].vertexes[0] = 8;
  exp.polygons[1].vertexes[1] = 7;
  exp.polygons[1].vertexes[2] = 6;

  exp.polygons[2].vertexes[0] = 5;
  exp.polygons[2].vertexes[1] = 6;
  exp.polygons[2].vertexes[2] = 2;

  exp.polygons[3].vertexes[0] = 6;
  exp.polygons[3].vertexes[1] = 7;
  exp.polygons[3].vertexes[2] = 3;

  exp.polygons[4].vertexes[0] = 3;
  exp.polygons[4].vertexes[1] = 7;
  exp.polygons[4].vertexes[2] = 8;

  exp.polygons[5].vertexes[0] = 1;
  exp.polygons[5].vertexes[1] = 4;
  exp.polygons[5].vertexes[2] = 8;

  exp.polygons[6].vertexes[0] = 1;
  exp.polygons[6].vertexes[1] = 2;
  exp.polygons[6].vertexes[2] = 4;

  exp.polygons[7].vertexes[0] = 5;
  exp.polygons[7].vertexes[1] = 8;
  exp.polygons[7].vertexes[2] = 6;

  exp.polygons[8].vertexes[0] = 1;
  exp.polygons[8].vertexes[1] = 5;
  exp.polygons[8].vertexes[2] = 2;

  exp.polygons[9].vertexes[0] = 2;
  exp.polygons[9].vertexes[1] = 6;
  exp.polygons[9].vertexes[2] = 3;

  exp.polygons[10].vertexes[0] = 4;
  exp.polygons[10].vertexes[1] = 3;
  exp.polygons[10].vertexes[2] = 8;

  exp.polygons[11].vertexes[0] = 5;
  exp.polygons[11].vertexes[1] = 1;
  exp.polygons[11].vertexes[2] = 8;

  struct data data = start("obj_files/cube.obj");

  int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);

  int is_polygons_eq = 1;
  for (int i = 0; i < data.count_of_facets; i++) {
    for (int j = 0; j < 3; j++) {
      if (data.polygons[i].vertexes[j] != exp.polygons[i].vertexes[j]) {
        is_polygons_eq = 0;
        break;
      }
    }
    if (is_polygons_eq == 0) {
      break;
    }
  }
  remove_matrix(&exp);
  ck_assert_int_eq(is_matrix_eq, 1);
  ck_assert_int_eq(is_polygons_eq, 1);
}
END_TEST

START_TEST(t_move_x) {
  struct data exp;
  exp = s21_create_data(8, 12);
  exp.count_of_vertexes = 36;
  exp.matrix_3d.matrix[0][0] = 2.0;
  exp.matrix_3d.matrix[0][1] = -1.0;
  exp.matrix_3d.matrix[0][2] = -1.0;

  exp.matrix_3d.matrix[1][0] = 2.0;
  exp.matrix_3d.matrix[1][1] = -1.0;
  exp.matrix_3d.matrix[1][2] = 1.0;

  exp.matrix_3d.matrix[2][0] = 0.0;
  exp.matrix_3d.matrix[2][1] = -1.0;
  exp.matrix_3d.matrix[2][2] = 1.0;

  exp.matrix_3d.matrix[3][0] = 0.0;
  exp.matrix_3d.matrix[3][1] = -1.0;
  exp.matrix_3d.matrix[3][2] = -1.0;

  exp.matrix_3d.matrix[4][0] = 2.0;
  exp.matrix_3d.matrix[4][1] = 1.0;
  exp.matrix_3d.matrix[4][2] = -0.999999;

  exp.matrix_3d.matrix[5][0] = 1.999999;
  exp.matrix_3d.matrix[5][1] = 1.0;
  exp.matrix_3d.matrix[5][2] = 1.000001;

  exp.matrix_3d.matrix[6][0] = 0.0;
  exp.matrix_3d.matrix[6][1] = 1.0;
  exp.matrix_3d.matrix[6][2] = 1.0;

  exp.matrix_3d.matrix[7][0] = 0.0;
  exp.matrix_3d.matrix[7][1] = 1.0;
  exp.matrix_3d.matrix[7][2] = -1.0;

  struct data data = start(file_name);
  move_x(&data.matrix_3d, 1.0);
  int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);
  ck_assert_int_eq(is_matrix_eq, 1);
  remove_matrix(&exp);
}
END_TEST

START_TEST(t_move_y) {
  struct data exp;
  exp = s21_create_data(8, 12);
  exp.count_of_vertexes = 36;
  exp.matrix_3d.matrix[0][0] = 1.0;
  exp.matrix_3d.matrix[0][1] = 0.0;
  exp.matrix_3d.matrix[0][2] = -1.0;

  exp.matrix_3d.matrix[1][0] = 1.0;
  exp.matrix_3d.matrix[1][1] = 0.0;
  exp.matrix_3d.matrix[1][2] = 1.0;

  exp.matrix_3d.matrix[2][0] = -1.0;
  exp.matrix_3d.matrix[2][1] = 0.0;
  exp.matrix_3d.matrix[2][2] = 1.0;

  exp.matrix_3d.matrix[3][0] = -1.0;
  exp.matrix_3d.matrix[3][1] = 0.0;
  exp.matrix_3d.matrix[3][2] = -1.0;

  exp.matrix_3d.matrix[4][0] = 1.0;
  exp.matrix_3d.matrix[4][1] = 2.0;
  exp.matrix_3d.matrix[4][2] = -0.999999;

  exp.matrix_3d.matrix[5][0] = 0.999999;
  exp.matrix_3d.matrix[5][1] = 2.0;
  exp.matrix_3d.matrix[5][2] = 1.000001;

  exp.matrix_3d.matrix[6][0] = -1.0;
  exp.matrix_3d.matrix[6][1] = 2.0;
  exp.matrix_3d.matrix[6][2] = 1.0;

  exp.matrix_3d.matrix[7][0] = -1.0;
  exp.matrix_3d.matrix[7][1] = 2.0;
  exp.matrix_3d.matrix[7][2] = -1.0;

  struct data data = start(file_name);
  move_y(&data.matrix_3d, 1.0);
  int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);
  ck_assert_int_eq(is_matrix_eq, 1);
  remove_matrix(&exp);
}
END_TEST

START_TEST(t_move_z) {
  struct data exp;
  exp = s21_create_data(8, 12);
  exp.count_of_vertexes = 36;
  exp.matrix_3d.matrix[0][0] = 1.0;
  exp.matrix_3d.matrix[0][1] = -1.0;
  exp.matrix_3d.matrix[0][2] = 0.0;

  exp.matrix_3d.matrix[1][0] = 1.0;
  exp.matrix_3d.matrix[1][1] = -1.0;
  exp.matrix_3d.matrix[1][2] = 2.0;

  exp.matrix_3d.matrix[2][0] = -1.0;
  exp.matrix_3d.matrix[2][1] = -1.0;
  exp.matrix_3d.matrix[2][2] = 2.0;

  exp.matrix_3d.matrix[3][0] = -1.0;
  exp.matrix_3d.matrix[3][1] = -1.0;
  exp.matrix_3d.matrix[3][2] = 0.0;

  exp.matrix_3d.matrix[4][0] = 1.0;
  exp.matrix_3d.matrix[4][1] = 1.0;
  exp.matrix_3d.matrix[4][2] = 0.000001;

  exp.matrix_3d.matrix[5][0] = 0.999999;
  exp.matrix_3d.matrix[5][1] = 1.0;
  exp.matrix_3d.matrix[5][2] = 2.000001;

  exp.matrix_3d.matrix[6][0] = -1.0;
  exp.matrix_3d.matrix[6][1] = 1.0;
  exp.matrix_3d.matrix[6][2] = 2.0;

  exp.matrix_3d.matrix[7][0] = -1.0;
  exp.matrix_3d.matrix[7][1] = 1.0;
  exp.matrix_3d.matrix[7][2] = 0.0;

  struct data data = start(file_name);
  move_z(&data.matrix_3d, 1.0);
  int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);
  ck_assert_int_eq(is_matrix_eq, 1);
  remove_matrix(&exp);
}
END_TEST

START_TEST(t_scale_xyz) {
  struct data exp;
  exp = s21_create_data(8, 12);
  exp.count_of_vertexes = 36;
  exp.matrix_3d.matrix[0][0] = 1.0 * 2;
  exp.matrix_3d.matrix[0][1] = -1.0 * 2;
  exp.matrix_3d.matrix[0][2] = -1.0 * 2;

  exp.matrix_3d.matrix[1][0] = 1.0 * 2;
  exp.matrix_3d.matrix[1][1] = -1.0 * 2;
  exp.matrix_3d.matrix[1][2] = 1.0 * 2;

  exp.matrix_3d.matrix[2][0] = -1.0 * 2;
  exp.matrix_3d.matrix[2][1] = -1.0 * 2;
  exp.matrix_3d.matrix[2][2] = 1.0 * 2;

  exp.matrix_3d.matrix[3][0] = -1.0 * 2;
  exp.matrix_3d.matrix[3][1] = -1.0 * 2;
  exp.matrix_3d.matrix[3][2] = -1.0 * 2;

  exp.matrix_3d.matrix[4][0] = 1.0 * 2;
  exp.matrix_3d.matrix[4][1] = 1.0 * 2;
  exp.matrix_3d.matrix[4][2] = -0.999999 * 2;

  exp.matrix_3d.matrix[5][0] = 0.999999 * 2;
  exp.matrix_3d.matrix[5][1] = 1.0 * 2;
  exp.matrix_3d.matrix[5][2] = 1.000001 * 2;

  exp.matrix_3d.matrix[6][0] = -1.0 * 2;
  exp.matrix_3d.matrix[6][1] = 1.0 * 2;
  exp.matrix_3d.matrix[6][2] = 1.0 * 2;

  exp.matrix_3d.matrix[7][0] = -1.0 * 2;
  exp.matrix_3d.matrix[7][1] = 1.0 * 2;
  exp.matrix_3d.matrix[7][2] = -1.0 * 2;

  struct data data = start(file_name);
  scale_xyz(&data.matrix_3d, 2.0);
  int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);
  ck_assert_int_eq(is_matrix_eq, 1);
  remove_matrix(&exp);
}
END_TEST

START_TEST(t_rotation_x) {
  struct data exp;
  exp = s21_create_data(8, 12);
  exp.count_of_vertexes = 36;
  exp.matrix_3d.matrix[0][0] = 1.0;
  exp.matrix_3d.matrix[0][1] = -0.366025;
  exp.matrix_3d.matrix[0][2] = -1.366025;

  exp.matrix_3d.matrix[1][0] = 1.0;
  exp.matrix_3d.matrix[1][1] = -1.366025;
  exp.matrix_3d.matrix[1][2] = 0.366025;

  exp.matrix_3d.matrix[2][0] = -1.0;
  exp.matrix_3d.matrix[2][1] = -1.366025;
  exp.matrix_3d.matrix[2][2] = 0.366025;

  exp.matrix_3d.matrix[3][0] = -1.0;
  exp.matrix_3d.matrix[3][1] = -0.366025;
  exp.matrix_3d.matrix[3][2] = -1.366025;

  exp.matrix_3d.matrix[4][0] = 1.0;
  exp.matrix_3d.matrix[4][1] = 1.366025;
  exp.matrix_3d.matrix[4][2] = -0.366025;

  exp.matrix_3d.matrix[5][0] = 0.999999;
  exp.matrix_3d.matrix[5][1] = 0.366025;
  exp.matrix_3d.matrix[5][2] = 1.366026;

  exp.matrix_3d.matrix[6][0] = -1.0;
  exp.matrix_3d.matrix[6][1] = 0.366025;
  exp.matrix_3d.matrix[6][2] = 1.366025;

  exp.matrix_3d.matrix[7][0] = -1.0;
  exp.matrix_3d.matrix[7][1] = 1.366025;
  exp.matrix_3d.matrix[7][2] = -0.366025;

  struct data data = start(file_name);
  rotation_x(&data.matrix_3d, 30.0);
  int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);
  ck_assert_int_eq(is_matrix_eq, 1);
  remove_matrix(&exp);
}
END_TEST

START_TEST(t_rotation_y) {
  struct data exp;
  exp = s21_create_data(8, 12);
  exp.count_of_vertexes = 36;
  exp.matrix_3d.matrix[0][0] = 1.366025;
  exp.matrix_3d.matrix[0][1] = -1.0;
  exp.matrix_3d.matrix[0][2] = -0.366025;

  exp.matrix_3d.matrix[1][0] = 0.366025;
  exp.matrix_3d.matrix[1][1] = -1.0;
  exp.matrix_3d.matrix[1][2] = 1.366025;

  exp.matrix_3d.matrix[2][0] = -1.366025;
  exp.matrix_3d.matrix[2][1] = -1.0;
  exp.matrix_3d.matrix[2][2] = 0.366025;

  exp.matrix_3d.matrix[3][0] = -0.366025;
  exp.matrix_3d.matrix[3][1] = -1.0;
  exp.matrix_3d.matrix[3][2] = -1.366025;

  exp.matrix_3d.matrix[4][0] = 1.366025;
  exp.matrix_3d.matrix[4][1] = 1.0;
  exp.matrix_3d.matrix[4][2] = -0.366025;

  exp.matrix_3d.matrix[5][0] = 0.366025;
  exp.matrix_3d.matrix[5][1] = 1.0;
  exp.matrix_3d.matrix[5][2] = 1.366025;

  exp.matrix_3d.matrix[6][0] = -1.366025;
  exp.matrix_3d.matrix[6][1] = 1.0;
  exp.matrix_3d.matrix[6][2] = 0.366025;

  exp.matrix_3d.matrix[7][0] = -0.366025;
  exp.matrix_3d.matrix[7][1] = 1.0;
  exp.matrix_3d.matrix[7][2] = -1.366025;

  struct data data = start(file_name);
  rotation_y(&data.matrix_3d, 30.0);
  int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);
  ck_assert_int_eq(is_matrix_eq, 1);
  remove_matrix(&exp);
}
END_TEST

START_TEST(t_rotation_z) {
  struct data exp;
  exp = s21_create_data(8, 12);
  exp.count_of_vertexes = 36;
  exp.matrix_3d.matrix[0][0] = 1.366025;
  exp.matrix_3d.matrix[0][1] = -0.366025;
  exp.matrix_3d.matrix[0][2] = -1.0;

  exp.matrix_3d.matrix[1][0] = 1.366025;
  exp.matrix_3d.matrix[1][1] = -0.366025;
  exp.matrix_3d.matrix[1][2] = 1.0;

  exp.matrix_3d.matrix[2][0] = -0.366025;
  exp.matrix_3d.matrix[2][1] = -1.366025;
  exp.matrix_3d.matrix[2][2] = 1.0;

  exp.matrix_3d.matrix[3][0] = -0.366025;
  exp.matrix_3d.matrix[3][1] = -1.366025;
  exp.matrix_3d.matrix[3][2] = -1.0;

  exp.matrix_3d.matrix[4][0] = 0.366025;
  exp.matrix_3d.matrix[4][1] = 1.366025;
  exp.matrix_3d.matrix[4][2] = -0.999999;

  exp.matrix_3d.matrix[5][0] = 0.366025;
  exp.matrix_3d.matrix[5][1] = 1.366025;
  exp.matrix_3d.matrix[5][2] = 1.000001;

  exp.matrix_3d.matrix[6][0] = -1.366025;
  exp.matrix_3d.matrix[6][1] = 0.366025;
  exp.matrix_3d.matrix[6][2] = 1.0;

  exp.matrix_3d.matrix[7][0] = -1.366025;
  exp.matrix_3d.matrix[7][1] = 0.366025;
  exp.matrix_3d.matrix[7][2] = -1.0;

  struct data data = start(file_name);
  rotation_z(&data.matrix_3d, 30.0);
  int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);
  ck_assert_int_eq(is_matrix_eq, 1);
  remove_matrix(&exp);
}
END_TEST

START_TEST(scale_x_1) {
  struct data exp;
  exp = s21_create_data(8, 12);
  exp.count_of_vertexes = 36;
  exp.matrix_3d.matrix[0][0] = 1.0;
  exp.matrix_3d.matrix[0][1] = -1.0;
  exp.matrix_3d.matrix[0][2] = -1.0;

  exp.matrix_3d.matrix[1][0] = 1.0;
  exp.matrix_3d.matrix[1][1] = -1.0;
  exp.matrix_3d.matrix[1][2] = 1.0;

  exp.matrix_3d.matrix[2][0] = -1.0;
  exp.matrix_3d.matrix[2][1] = -1.0;
  exp.matrix_3d.matrix[2][2] = 1.0;

  exp.matrix_3d.matrix[3][0] = -1.0;
  exp.matrix_3d.matrix[3][1] = -1.0;
  exp.matrix_3d.matrix[3][2] = -1.0;

  exp.matrix_3d.matrix[4][0] = 1.0;
  exp.matrix_3d.matrix[4][1] = 1.0;
  exp.matrix_3d.matrix[4][2] = -0.999999;

  exp.matrix_3d.matrix[5][0] = 0.999999;
  exp.matrix_3d.matrix[5][1] = 1.0;
  exp.matrix_3d.matrix[5][2] = 1.000001;

  exp.matrix_3d.matrix[6][0] = -1.0;
  exp.matrix_3d.matrix[6][1] = 1.0;
  exp.matrix_3d.matrix[6][2] = 1.0;

  exp.matrix_3d.matrix[7][0] = -1.0;
  exp.matrix_3d.matrix[7][1] = 1.0;
  exp.matrix_3d.matrix[7][2] = -1.0;

  struct data data = start(file_name);
  scale_x(&data.matrix_3d, 1);
  int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);
  ck_assert_int_eq(is_matrix_eq, 1);
  remove_matrix(&exp);
}
END_TEST

START_TEST(scale_x_2) {
  struct data exp;
  exp = s21_create_data(8, 12);
  exp.count_of_vertexes = 36;
  exp.matrix_3d.matrix[0][0] = 1.0;
  exp.matrix_3d.matrix[0][1] = -1.0;
  exp.matrix_3d.matrix[0][2] = -1.0;

  exp.matrix_3d.matrix[1][0] = 1.0;
  exp.matrix_3d.matrix[1][1] = -1.0;
  exp.matrix_3d.matrix[1][2] = 1.0;

  exp.matrix_3d.matrix[2][0] = -1.0;
  exp.matrix_3d.matrix[2][1] = -1.0;
  exp.matrix_3d.matrix[2][2] = 1.0;

  exp.matrix_3d.matrix[3][0] = -1.0;
  exp.matrix_3d.matrix[3][1] = -1.0;
  exp.matrix_3d.matrix[3][2] = -1.0;

  exp.matrix_3d.matrix[4][0] = 1.0;
  exp.matrix_3d.matrix[4][1] = 1.0;
  exp.matrix_3d.matrix[4][2] = -0.999999;

  exp.matrix_3d.matrix[5][0] = 0.999999;
  exp.matrix_3d.matrix[5][1] = 1.0;
  exp.matrix_3d.matrix[5][2] = 1.000001;

  exp.matrix_3d.matrix[6][0] = -1.0;
  exp.matrix_3d.matrix[6][1] = 1.0;
  exp.matrix_3d.matrix[6][2] = 1.0;

  exp.matrix_3d.matrix[7][0] = -1.0;
  exp.matrix_3d.matrix[7][1] = 1.0;
  exp.matrix_3d.matrix[7][2] = -1.0;

  struct data data = start(file_name);
  scale_x(&data.matrix_3d, -1);
  int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);
  ck_assert_int_eq(is_matrix_eq, 1);
  remove_matrix(&exp);
}
END_TEST

START_TEST(scale_y_1) {
  struct data exp;
  exp = s21_create_data(8, 12);
  exp.count_of_vertexes = 36;
  exp.matrix_3d.matrix[0][0] = 1.0;
  exp.matrix_3d.matrix[0][1] = -1.0;
  exp.matrix_3d.matrix[0][2] = -1.0;

  exp.matrix_3d.matrix[1][0] = 1.0;
  exp.matrix_3d.matrix[1][1] = -1.0;
  exp.matrix_3d.matrix[1][2] = 1.0;

  exp.matrix_3d.matrix[2][0] = -1.0;
  exp.matrix_3d.matrix[2][1] = -1.0;
  exp.matrix_3d.matrix[2][2] = 1.0;

  exp.matrix_3d.matrix[3][0] = -1.0;
  exp.matrix_3d.matrix[3][1] = -1.0;
  exp.matrix_3d.matrix[3][2] = -1.0;

  exp.matrix_3d.matrix[4][0] = 1.0;
  exp.matrix_3d.matrix[4][1] = 1.0;
  exp.matrix_3d.matrix[4][2] = -0.999999;

  exp.matrix_3d.matrix[5][0] = 0.999999;
  exp.matrix_3d.matrix[5][1] = 1.0;
  exp.matrix_3d.matrix[5][2] = 1.000001;

  exp.matrix_3d.matrix[6][0] = -1.0;
  exp.matrix_3d.matrix[6][1] = 1.0;
  exp.matrix_3d.matrix[6][2] = 1.0;

  exp.matrix_3d.matrix[7][0] = -1.0;
  exp.matrix_3d.matrix[7][1] = 1.0;
  exp.matrix_3d.matrix[7][2] = -1.0;

  struct data data = start(file_name);
  scale_y(&data.matrix_3d, 1);
  int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);
  ck_assert_int_eq(is_matrix_eq, 1);
  remove_matrix(&exp);
}
END_TEST

START_TEST(scale_y_2) {
  struct data exp;
  exp = s21_create_data(8, 12);
  exp.count_of_vertexes = 36;
  exp.matrix_3d.matrix[0][0] = 1.0;
  exp.matrix_3d.matrix[0][1] = -1.0;
  exp.matrix_3d.matrix[0][2] = -1.0;

  exp.matrix_3d.matrix[1][0] = 1.0;
  exp.matrix_3d.matrix[1][1] = -1.0;
  exp.matrix_3d.matrix[1][2] = 1.0;

  exp.matrix_3d.matrix[2][0] = -1.0;
  exp.matrix_3d.matrix[2][1] = -1.0;
  exp.matrix_3d.matrix[2][2] = 1.0;

  exp.matrix_3d.matrix[3][0] = -1.0;
  exp.matrix_3d.matrix[3][1] = -1.0;
  exp.matrix_3d.matrix[3][2] = -1.0;

  exp.matrix_3d.matrix[4][0] = 1.0;
  exp.matrix_3d.matrix[4][1] = 1.0;
  exp.matrix_3d.matrix[4][2] = -0.999999;

  exp.matrix_3d.matrix[5][0] = 0.999999;
  exp.matrix_3d.matrix[5][1] = 1.0;
  exp.matrix_3d.matrix[5][2] = 1.000001;

  exp.matrix_3d.matrix[6][0] = -1.0;
  exp.matrix_3d.matrix[6][1] = 1.0;
  exp.matrix_3d.matrix[6][2] = 1.0;

  exp.matrix_3d.matrix[7][0] = -1.0;
  exp.matrix_3d.matrix[7][1] = 1.0;
  exp.matrix_3d.matrix[7][2] = -1.0;

  struct data data = start(file_name);
  scale_y(&data.matrix_3d, -1);
  int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);
  ck_assert_int_eq(is_matrix_eq, 1);
  remove_matrix(&exp);
}
END_TEST

START_TEST(scale_z_1) {
  struct data exp;
  exp = s21_create_data(8, 12);
  exp.count_of_vertexes = 36;
  exp.matrix_3d.matrix[0][0] = 1.0;
  exp.matrix_3d.matrix[0][1] = -1.0;
  exp.matrix_3d.matrix[0][2] = -1.0;

  exp.matrix_3d.matrix[1][0] = 1.0;
  exp.matrix_3d.matrix[1][1] = -1.0;
  exp.matrix_3d.matrix[1][2] = 1.0;

  exp.matrix_3d.matrix[2][0] = -1.0;
  exp.matrix_3d.matrix[2][1] = -1.0;
  exp.matrix_3d.matrix[2][2] = 1.0;

  exp.matrix_3d.matrix[3][0] = -1.0;
  exp.matrix_3d.matrix[3][1] = -1.0;
  exp.matrix_3d.matrix[3][2] = -1.0;

  exp.matrix_3d.matrix[4][0] = 1.0;
  exp.matrix_3d.matrix[4][1] = 1.0;
  exp.matrix_3d.matrix[4][2] = -0.999999;

  exp.matrix_3d.matrix[5][0] = 0.999999;
  exp.matrix_3d.matrix[5][1] = 1.0;
  exp.matrix_3d.matrix[5][2] = 1.000001;

  exp.matrix_3d.matrix[6][0] = -1.0;
  exp.matrix_3d.matrix[6][1] = 1.0;
  exp.matrix_3d.matrix[6][2] = 1.0;

  exp.matrix_3d.matrix[7][0] = -1.0;
  exp.matrix_3d.matrix[7][1] = 1.0;
  exp.matrix_3d.matrix[7][2] = -1.0;

  struct data data = start(file_name);
  scale_z(&data.matrix_3d, 1);
  int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);
  ck_assert_int_eq(is_matrix_eq, 1);
  remove_matrix(&exp);
}
END_TEST

START_TEST(scale_z_2) {
  struct data exp;
  exp = s21_create_data(8, 12);
  exp.count_of_vertexes = 36;
  exp.matrix_3d.matrix[0][0] = 1.0;
  exp.matrix_3d.matrix[0][1] = -1.0;
  exp.matrix_3d.matrix[0][2] = -1.0;

  exp.matrix_3d.matrix[1][0] = 1.0;
  exp.matrix_3d.matrix[1][1] = -1.0;
  exp.matrix_3d.matrix[1][2] = 1.0;

  exp.matrix_3d.matrix[2][0] = -1.0;
  exp.matrix_3d.matrix[2][1] = -1.0;
  exp.matrix_3d.matrix[2][2] = 1.0;

  exp.matrix_3d.matrix[3][0] = -1.0;
  exp.matrix_3d.matrix[3][1] = -1.0;
  exp.matrix_3d.matrix[3][2] = -1.0;

  exp.matrix_3d.matrix[4][0] = 1.0;
  exp.matrix_3d.matrix[4][1] = 1.0;
  exp.matrix_3d.matrix[4][2] = -0.999999;

  exp.matrix_3d.matrix[5][0] = 0.999999;
  exp.matrix_3d.matrix[5][1] = 1.0;
  exp.matrix_3d.matrix[5][2] = 1.000001;

  exp.matrix_3d.matrix[6][0] = -1.0;
  exp.matrix_3d.matrix[6][1] = 1.0;
  exp.matrix_3d.matrix[6][2] = 1.0;

  exp.matrix_3d.matrix[7][0] = -1.0;
  exp.matrix_3d.matrix[7][1] = 1.0;
  exp.matrix_3d.matrix[7][2] = -1.0;

  struct data data = start(file_name);
  scale_z(&data.matrix_3d, -1);
  int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);
  ck_assert_int_eq(is_matrix_eq, 1);
  remove_matrix(&exp);
}
END_TEST

START_TEST(scale_xyz_2) {
  struct data exp;
  exp = s21_create_data(8, 12);
  exp.count_of_vertexes = 36;
  exp.matrix_3d.matrix[0][0] = 1.0;
  exp.matrix_3d.matrix[0][1] = -1.0;
  exp.matrix_3d.matrix[0][2] = -1.0;

  exp.matrix_3d.matrix[1][0] = 1.0;
  exp.matrix_3d.matrix[1][1] = -1.0;
  exp.matrix_3d.matrix[1][2] = 1.0;

  exp.matrix_3d.matrix[2][0] = -1.0;
  exp.matrix_3d.matrix[2][1] = -1.0;
  exp.matrix_3d.matrix[2][2] = 1.0;

  exp.matrix_3d.matrix[3][0] = -1.0;
  exp.matrix_3d.matrix[3][1] = -1.0;
  exp.matrix_3d.matrix[3][2] = -1.0;

  exp.matrix_3d.matrix[4][0] = 1.0;
  exp.matrix_3d.matrix[4][1] = 1.0;
  exp.matrix_3d.matrix[4][2] = -0.999999;

  exp.matrix_3d.matrix[5][0] = 0.999999;
  exp.matrix_3d.matrix[5][1] = 1.0;
  exp.matrix_3d.matrix[5][2] = 1.000001;

  exp.matrix_3d.matrix[6][0] = -1.0;
  exp.matrix_3d.matrix[6][1] = 1.0;
  exp.matrix_3d.matrix[6][2] = 1.0;

  exp.matrix_3d.matrix[7][0] = -1.0;
  exp.matrix_3d.matrix[7][1] = 1.0;
  exp.matrix_3d.matrix[7][2] = -1.0;

  struct data data = start(file_name);
  scale_xyz(&data.matrix_3d, -1);
  int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);
  ck_assert_int_eq(is_matrix_eq, 1);
  remove_matrix(&exp);
}
END_TEST

START_TEST(poligon_1) {
  polygon_t p1 = s21_create_polygon(15);
  s21_remove_polygon(&p1);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, data_1);
  tcase_add_test(tc1_1, t_move_x);
  tcase_add_test(tc1_1, t_move_y);
  tcase_add_test(tc1_1, t_move_z);
  tcase_add_test(tc1_1, t_scale_xyz);
  tcase_add_test(tc1_1, t_rotation_x);
  tcase_add_test(tc1_1, t_rotation_y);
  tcase_add_test(tc1_1, t_rotation_z);
  tcase_add_test(tc1_1, scale_x_1);
  tcase_add_test(tc1_1, scale_x_2);
  tcase_add_test(tc1_1, scale_y_1);
  tcase_add_test(tc1_1, scale_y_2);
  tcase_add_test(tc1_1, scale_z_1);
  tcase_add_test(tc1_1, scale_z_2);
  tcase_add_test(tc1_1, scale_xyz_2);
  tcase_add_test(tc1_1, poligon_1);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}

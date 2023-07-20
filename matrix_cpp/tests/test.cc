#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(create_matrix_with_size, True) {
  S21Matrix m(3, 3);
  ASSERT_TRUE(3 == m.GetRows());
  ASSERT_TRUE(3 == m.GetCols());
}

TEST(create_matrix_loop, True) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  S21Matrix m(rows, cols);
  ASSERT_TRUE(rows == m.GetRows());
  ASSERT_TRUE(cols == m.GetCols());
}

TEST(create_matrix_copy, True) {
  S21Matrix m(4, 3);
  for (int i = 0; i < m.GetRows(); i++) {
    for (int j = 0; j < m.GetCols(); j++) {
      m.SetMatrixMember(i, j, i + j);
    }
  }
  S21Matrix m2(m);
  ASSERT_TRUE(m == m2);
}

TEST(create_matrix_move, True) {
  S21Matrix m(4, 3);
  S21Matrix m2 = std::move(m);
  ASSERT_TRUE(4 == m2.GetRows());
  ASSERT_TRUE(3 == m2.GetCols());
}

TEST(create_matrix, True) { S21Matrix m; }

TEST(eq_not_equal_size, False) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 2);
  ASSERT_FALSE(a == b);
}

TEST(eq_not_equal_value, False) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a.SetMatrixMember(i, j, i + 1);
      b.SetMatrixMember(i, j, i);
    }
  }
  ASSERT_FALSE(a == b);
}

TEST(eq_loop, True) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double rand_val = rand();
      a.SetMatrixMember(i, j, rand_val);
      b.SetMatrixMember(i, j, rand_val);
    }
  }
  ASSERT_TRUE(a == b);
}

TEST(sum_wrong_size, True) {
  S21Matrix a(3, 3);
  S21Matrix b(2, 2);
  try {
    a.SumMatrix(b);
  } catch (const char *err) {
  }
}

TEST(sum_loop, True) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);
  S21Matrix sum(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      a.SetMatrixMember(i, j, rand() % 100 + 1);
      b.SetMatrixMember(i, j, rand() % 100 + 1);
      sum.SetMatrixMember(i, j,
                          a.GetMatrixMember(i, j) + b.GetMatrixMember(i, j));
    }
  }
  a.SumMatrix(b);
  ASSERT_TRUE(a == sum);
}

TEST(sub_loop, True) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);
  S21Matrix sub(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      a.SetMatrixMember(i, j, rand() % 100 + 1);
      b.SetMatrixMember(i, j, rand() % 100 + 1);
      sub.SetMatrixMember(i, j,
                          a.GetMatrixMember(i, j) - b.GetMatrixMember(i, j));
    }
  }
  a.SubMatrix(b);
  ASSERT_TRUE(a == sub);
}

TEST(sub_wrong_size, True) {
  S21Matrix a(3, 3);
  S21Matrix b(2, 2);
  try {
    a.SubMatrix(b);
  } catch (const char *err) {
  }
}

TEST(mult_number_loop, True) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  S21Matrix a(rows, cols);
  S21Matrix check(rows, cols);
  double mult_number = 2;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      a.SetMatrixMember(i, j, rand() % 100 + 1);
      check.SetMatrixMember(i, j, a.GetMatrixMember(i, j) * mult_number);
    }
  }
  a.MulNumber(mult_number);
  ASSERT_TRUE(a == check);
}

TEST(mult_loop, True) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  S21Matrix a(rows, cols);
  S21Matrix b(cols, rows);
  S21Matrix check(rows, rows);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) a.SetMatrixMember(i, j, rand() % 100 + 1);
  for (int i = 0; i < cols; i++)
    for (int j = 0; j < rows; j++) b.SetMatrixMember(i, j, rand() % 100 + 1);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < b.GetCols(); j++) {
      check.SetMatrixMember(i, j, 0);
      for (int k = 0; k < a.GetCols(); k++)
        check.SetMatrixMember(
            i, j,
            check.GetMatrixMember(i, j) +
                a.GetMatrixMember(i, k) * b.GetMatrixMember(k, j));
    }
  }
  a.MulMatrix(b);
  ASSERT_TRUE(a == check);
  a.~S21Matrix();
}

TEST(mult, True) {
  const int rows = 2;
  const int cols = 3;
  S21Matrix a(2, 3);
  S21Matrix b(3, 2);
  S21Matrix check(2, 2);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) a.SetMatrixMember(i, j, c++);

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) b.SetMatrixMember(i, j, c++);

  check.SetMatrixMember(0, 0, 58);
  check.SetMatrixMember(0, 1, 64);
  check.SetMatrixMember(1, 0, 139);
  check.SetMatrixMember(1, 1, 154);

  a.MulMatrix(b);
  ASSERT_TRUE(a == check);
}

TEST(mult_matrix_wrong_size, True) {
  S21Matrix a(3, 3);
  S21Matrix b(2, 2);
  try {
    a.MulMatrix(b);
  } catch (const char *err) {
  }
}

TEST(transpose_loop, True) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  S21Matrix m(rows, cols);
  S21Matrix check(cols, rows);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double rand_val = rand() % 100 + 1;
      m.SetMatrixMember(i, j, rand_val);
      check.SetMatrixMember(j, i, rand_val);
    }
  }
  S21Matrix res = m.Transpose();
  ASSERT_TRUE(res == check);
}

TEST(complements_1, True) {
  S21Matrix m(3, 3);
  S21Matrix r(3, 3);
  m.SetMatrixMember(0, 0, 1);
  m.SetMatrixMember(0, 1, 2);
  m.SetMatrixMember(0, 2, 3);

  m.SetMatrixMember(1, 0, 0);
  m.SetMatrixMember(1, 1, 4);
  m.SetMatrixMember(1, 2, 2);

  m.SetMatrixMember(2, 0, 5);
  m.SetMatrixMember(2, 1, 2);
  m.SetMatrixMember(2, 2, 1);

  r.SetMatrixMember(0, 0, 0);
  r.SetMatrixMember(0, 1, 10);
  r.SetMatrixMember(0, 2, -20);

  r.SetMatrixMember(1, 0, 4);
  r.SetMatrixMember(1, 1, -14);
  r.SetMatrixMember(1, 2, 8);

  r.SetMatrixMember(2, 0, -8);
  r.SetMatrixMember(2, 1, -2);
  r.SetMatrixMember(2, 2, 4);

  S21Matrix res(m.CalcComplements());
  ASSERT_TRUE(res == r);
}

TEST(complements_wrong_size, True) {
  S21Matrix a(3, 2);
  try {
    a.CalcComplements();
  } catch (const char *err) {
  }
}

TEST(complements_2, True) {
  S21Matrix m(3, 3);
  S21Matrix r(3, 3);

  m.SetMatrixMember(0, 0, 5);
  m.SetMatrixMember(0, 1, -1);
  m.SetMatrixMember(0, 2, 1);

  m.SetMatrixMember(1, 0, 2);
  m.SetMatrixMember(1, 1, 3);
  m.SetMatrixMember(1, 2, 4);

  m.SetMatrixMember(2, 0, 1);
  m.SetMatrixMember(2, 1, 0);
  m.SetMatrixMember(2, 2, 3);

  r.SetMatrixMember(0, 0, 9);
  r.SetMatrixMember(0, 1, -2);
  r.SetMatrixMember(0, 2, -3);

  r.SetMatrixMember(1, 0, 3);
  r.SetMatrixMember(1, 1, 14);
  r.SetMatrixMember(1, 2, -1);

  r.SetMatrixMember(2, 0, -7);
  r.SetMatrixMember(2, 1, -18);
  r.SetMatrixMember(2, 2, 17);

  S21Matrix res(m.CalcComplements());
  ASSERT_TRUE(res == r);
}

TEST(complements_3, True) {
  S21Matrix m(1, 1);
  S21Matrix r(1, 1);
  m.SetMatrixMember(0, 0, 5);
  r.SetMatrixMember(0, 0, 1);
  S21Matrix res(m.CalcComplements());
  ASSERT_TRUE(res == r);
}

TEST(determinant_1, True) {
  double expected = 11;
  S21Matrix m(2, 2);
  m.SetMatrixMember(0, 0, 1);
  m.SetMatrixMember(0, 1, 3);
  m.SetMatrixMember(1, 0, -2);
  m.SetMatrixMember(1, 1, 5);
  double result = m.Determinant();
  ASSERT_TRUE(result == expected);
}

TEST(determinant_2, True) {
  double expected = -7;
  S21Matrix m(3, 3);
  m.SetMatrixMember(0, 0, 1);
  m.SetMatrixMember(0, 1, 0);
  m.SetMatrixMember(0, 2, -2);
  m.SetMatrixMember(1, 0, 0.5);
  m.SetMatrixMember(1, 1, 3);
  m.SetMatrixMember(1, 2, 1);
  m.SetMatrixMember(2, 0, 0);
  m.SetMatrixMember(2, 1, 2);
  m.SetMatrixMember(2, 2, -1);
  double result = m.Determinant();
  ASSERT_TRUE(result == expected);
}

TEST(determinant_3, True) {
  double expected = 1;
  S21Matrix m(1, 1);
  m.SetMatrixMember(0, 0, 1);
  double result = m.Determinant();
  ASSERT_TRUE(result == expected);
}

TEST(determinant_4, True) {
  double expected = 0;
  S21Matrix m(5, 5);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      m.SetMatrixMember(i, j, j);
    }
  }
  double result = m.Determinant();
  ASSERT_TRUE(result == expected);
}

TEST(determinant_5, True) {
  double expected = 0;
  S21Matrix m(4, 4);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      m.SetMatrixMember(i, j, j + i);
    }
  }
  double result = m.Determinant();
  ASSERT_TRUE(result == expected);
}

TEST(determinant_7, True) {
  double expected = 7;
  S21Matrix m(2, 2);
  m.SetMatrixMember(0, 0, -5);
  m.SetMatrixMember(0, 1, -4);
  m.SetMatrixMember(1, 0, -2);
  m.SetMatrixMember(1, 1, -3);
  double result = m.Determinant();
  ASSERT_TRUE(result == expected);
}

TEST(determinant_8, True) {
  double expected = 0;
  S21Matrix m(3, 3);
  m.SetMatrixMember(0, 0, 1);
  m.SetMatrixMember(0, 1, 2);
  m.SetMatrixMember(0, 2, 3);
  m.SetMatrixMember(1, 0, 4);
  m.SetMatrixMember(1, 1, 5);
  m.SetMatrixMember(1, 2, 6);
  m.SetMatrixMember(2, 0, 7);
  m.SetMatrixMember(2, 1, 8);
  m.SetMatrixMember(2, 2, 9);
  double result = m.Determinant();
  ASSERT_TRUE(result == expected);
}

TEST(determinant_9, True) {
  double expected = 30;
  S21Matrix m(4, 4);
  m.SetMatrixMember(0, 0, 1);
  m.SetMatrixMember(0, 1, 0);
  m.SetMatrixMember(0, 2, 2);
  m.SetMatrixMember(0, 3, -1);

  m.SetMatrixMember(1, 0, 3);
  m.SetMatrixMember(1, 1, 0);
  m.SetMatrixMember(1, 2, 0);
  m.SetMatrixMember(1, 3, 5);

  m.SetMatrixMember(2, 0, 2);
  m.SetMatrixMember(2, 1, 1);
  m.SetMatrixMember(2, 2, 4);
  m.SetMatrixMember(2, 3, -3);

  m.SetMatrixMember(3, 0, 1);
  m.SetMatrixMember(3, 1, 0);
  m.SetMatrixMember(3, 2, 5);
  m.SetMatrixMember(3, 3, 0);
  double result = m.Determinant();
  ASSERT_TRUE(result == expected);
}

TEST(determinant_wrong_size, True) {
  S21Matrix a(3, 2);
  try {
    a.Determinant();
  } catch (const char *err) {
  }
}

TEST(inverse_1, True) {
  S21Matrix m(3, 3);
  m.SetMatrixMember(0, 0, 2);
  m.SetMatrixMember(0, 1, 5);
  m.SetMatrixMember(0, 2, 7);
  m.SetMatrixMember(1, 0, 6);
  m.SetMatrixMember(1, 1, 3);
  m.SetMatrixMember(1, 2, 4);
  m.SetMatrixMember(2, 0, 5);
  m.SetMatrixMember(2, 1, -2);
  m.SetMatrixMember(2, 2, -3);
  S21Matrix r(3, 3);
  r.SetMatrixMember(0, 0, 1);
  r.SetMatrixMember(0, 1, -1);
  r.SetMatrixMember(0, 2, 1);
  r.SetMatrixMember(1, 0, -38);
  r.SetMatrixMember(1, 1, 41);
  r.SetMatrixMember(1, 2, -34);
  r.SetMatrixMember(2, 0, 27);
  r.SetMatrixMember(2, 1, -29);
  r.SetMatrixMember(2, 2, 24);
  S21Matrix res(m.InverseMatrix());
  ASSERT_TRUE(res == r);
}

TEST(inverse_2, True) {
  S21Matrix m(3, 3);
  m.SetMatrixMember(0, 0, 1);
  m.SetMatrixMember(0, 1, -1);
  m.SetMatrixMember(0, 2, 1);
  m.SetMatrixMember(1, 0, -38);
  m.SetMatrixMember(1, 1, 41);
  m.SetMatrixMember(1, 2, -34);
  m.SetMatrixMember(2, 0, 27);
  m.SetMatrixMember(2, 1, -29);
  m.SetMatrixMember(2, 2, 24);
  S21Matrix r(3, 3);
  r.SetMatrixMember(0, 0, 2);
  r.SetMatrixMember(0, 1, 5);
  r.SetMatrixMember(0, 2, 7);
  r.SetMatrixMember(1, 0, 6);
  r.SetMatrixMember(1, 1, 3);
  r.SetMatrixMember(1, 2, 4);
  r.SetMatrixMember(2, 0, 5);
  r.SetMatrixMember(2, 1, -2);
  r.SetMatrixMember(2, 2, -3);
  S21Matrix res(r.InverseMatrix());
  ASSERT_TRUE(res == m);
}

TEST(inverse_wrong_size, True) {
  S21Matrix m(5, 5);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      m.SetMatrixMember(i, j, j);
    }
  }
  try {
    m.InverseMatrix();
  } catch (const char *err) {
  }
}

TEST(inverse_3, True) {
  S21Matrix m(1, 1);
  m.SetMatrixMember(0, 0, 2);
  S21Matrix r(1, 1);
  r.SetMatrixMember(0, 0, 0.5);
  S21Matrix res(m.InverseMatrix());
  ASSERT_TRUE(r == res);
}

TEST(op_plus, True) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  a.SetMatrixMember(0, 0, 1);
  a.SetMatrixMember(0, 1, 1);
  a.SetMatrixMember(1, 0, 1);
  a.SetMatrixMember(1, 1, 1);
  b.SetMatrixMember(0, 0, 1);
  b.SetMatrixMember(0, 1, 1);
  b.SetMatrixMember(1, 0, 1);
  b.SetMatrixMember(1, 1, 1);
  c.SetMatrixMember(0, 0, 2);
  c.SetMatrixMember(0, 1, 2);
  c.SetMatrixMember(1, 0, 2);
  c.SetMatrixMember(1, 1, 2);
  S21Matrix m(a + b);
  ASSERT_TRUE(c == m);
}

TEST(op_minus, True) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  a.SetMatrixMember(0, 0, 1);
  a.SetMatrixMember(0, 1, 1);
  a.SetMatrixMember(1, 0, 1);
  a.SetMatrixMember(1, 1, 1);
  b.SetMatrixMember(0, 0, 1);
  b.SetMatrixMember(0, 1, 1);
  b.SetMatrixMember(1, 0, 1);
  b.SetMatrixMember(1, 1, 1);
  c.SetMatrixMember(0, 0, 0);
  c.SetMatrixMember(0, 1, 0);
  c.SetMatrixMember(1, 0, 0);
  c.SetMatrixMember(1, 1, 0);
  S21Matrix m(a - b);
  ASSERT_TRUE(c == m);
}

TEST(op_mult_matrix, True) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  a.SetMatrixMember(0, 0, 2);
  a.SetMatrixMember(0, 1, 2);
  a.SetMatrixMember(1, 0, 2);
  a.SetMatrixMember(1, 1, 2);
  b.SetMatrixMember(0, 0, 1);
  b.SetMatrixMember(0, 1, 1);
  b.SetMatrixMember(1, 0, 1);
  b.SetMatrixMember(1, 1, 1);
  c.SetMatrixMember(0, 0, 4);
  c.SetMatrixMember(0, 1, 4);
  c.SetMatrixMember(1, 0, 4);
  c.SetMatrixMember(1, 1, 4);
  S21Matrix m(a * b);
  ASSERT_TRUE(c == m);
}

TEST(op_mult_number, True) {
  S21Matrix a(2, 2);
  S21Matrix c(2, 2);
  int n = 2;
  a.SetMatrixMember(0, 0, 2);
  a.SetMatrixMember(0, 1, 2);
  a.SetMatrixMember(1, 0, 2);
  a.SetMatrixMember(1, 1, 2);
  c.SetMatrixMember(0, 0, 4);
  c.SetMatrixMember(0, 1, 4);
  c.SetMatrixMember(1, 0, 4);
  c.SetMatrixMember(1, 1, 4);
  S21Matrix m(a * n);
  ASSERT_TRUE(c == m);
}

TEST(op_is_equal, True) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a.SetMatrixMember(0, 0, 2);
  a.SetMatrixMember(0, 1, 2);
  a.SetMatrixMember(1, 0, 2);
  a.SetMatrixMember(1, 1, 2);
  b.SetMatrixMember(0, 0, 2);
  b.SetMatrixMember(0, 1, 2);
  b.SetMatrixMember(1, 0, 2);
  b.SetMatrixMember(1, 1, 2);
  ASSERT_TRUE(a == b);
}

TEST(op_is_equal_2, False) {
  S21Matrix a(2, 2);
  S21Matrix c(2, 2);
  a.SetMatrixMember(0, 0, 2);
  a.SetMatrixMember(0, 1, 2);
  a.SetMatrixMember(1, 0, 2);
  a.SetMatrixMember(1, 1, 2);

  c.SetMatrixMember(0, 0, 4);
  c.SetMatrixMember(0, 1, 4);
  c.SetMatrixMember(1, 0, 4);
  c.SetMatrixMember(1, 1, 4);
  ASSERT_FALSE(a == c);
}

TEST(op_equals, True) {
  S21Matrix a(2, 2);
  S21Matrix c(3, 3);
  a = c;
  ASSERT_TRUE(a == c);
}

TEST(op_equals_2, True) {
  S21Matrix a(3, 3);
  S21Matrix c(2, 2);
  a = c;
  ASSERT_TRUE(a == c);
}

TEST(op_plus_eq, True) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  a.SetMatrixMember(0, 0, 1);
  a.SetMatrixMember(0, 1, 1);
  a.SetMatrixMember(1, 0, 1);
  a.SetMatrixMember(1, 1, 1);
  b.SetMatrixMember(0, 0, 1);
  b.SetMatrixMember(0, 1, 1);
  b.SetMatrixMember(1, 0, 1);
  b.SetMatrixMember(1, 1, 1);
  c.SetMatrixMember(0, 0, 2);
  c.SetMatrixMember(0, 1, 2);
  c.SetMatrixMember(1, 0, 2);
  c.SetMatrixMember(1, 1, 2);
  a += b;
  ASSERT_TRUE(a == c);
}

TEST(op_minus_eq, True) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  a.SetMatrixMember(0, 0, 1);
  a.SetMatrixMember(0, 1, 1);
  a.SetMatrixMember(1, 0, 1);
  a.SetMatrixMember(1, 1, 1);
  b.SetMatrixMember(0, 0, 1);
  b.SetMatrixMember(0, 1, 1);
  b.SetMatrixMember(1, 0, 1);
  b.SetMatrixMember(1, 1, 1);
  c.SetMatrixMember(0, 0, 0);
  c.SetMatrixMember(0, 1, 0);
  c.SetMatrixMember(1, 0, 0);
  c.SetMatrixMember(1, 1, 0);
  a -= b;
  ASSERT_TRUE(a == c);
}

TEST(op_mult_matrix_eq, True) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  a.SetMatrixMember(0, 0, 2);
  a.SetMatrixMember(0, 1, 2);
  a.SetMatrixMember(1, 0, 2);
  a.SetMatrixMember(1, 1, 2);
  b.SetMatrixMember(0, 0, 1);
  b.SetMatrixMember(0, 1, 1);
  b.SetMatrixMember(1, 0, 1);
  b.SetMatrixMember(1, 1, 1);
  c.SetMatrixMember(0, 0, 4);
  c.SetMatrixMember(0, 1, 4);
  c.SetMatrixMember(1, 0, 4);
  c.SetMatrixMember(1, 1, 4);
  a *= b;
  ASSERT_TRUE(a == c);
}

TEST(op_mult_number_eq, True) {
  S21Matrix a(2, 2);
  S21Matrix c(2, 2);
  int n = 2;
  a.SetMatrixMember(0, 0, 2);
  a.SetMatrixMember(0, 1, 2);
  a.SetMatrixMember(1, 0, 2);
  a.SetMatrixMember(1, 1, 2);
  c.SetMatrixMember(0, 0, 4);
  c.SetMatrixMember(0, 1, 4);
  c.SetMatrixMember(1, 0, 4);
  c.SetMatrixMember(1, 1, 4);
  a *= n;
  ASSERT_TRUE(a == c);
}

TEST(op_braces, True) {
  S21Matrix a(2, 2);
  a.SetMatrixMember(0, 0, 1);
  a.SetMatrixMember(0, 1, 2);
  a.SetMatrixMember(1, 0, 3);
  a.SetMatrixMember(1, 1, 4);
  double n = a(0, 0);
  ASSERT_TRUE(1 == n);
  n = a(0, 1);
  ASSERT_TRUE(n == 2);
}

TEST(braces_out_of_range, True) {
  S21Matrix m(2, 2);
  try {
    double n = m(5, 5);
    ASSERT_TRUE(1 == n);
  } catch (const char *err) {
  }
}
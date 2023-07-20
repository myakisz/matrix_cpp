#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <math.h>

class S21Matrix {
 private:
  int rows_, cols_;
  // Pointer to the memory where the matrix is allocated
  double **matrix_;

 public:
  // Базовый конструктор, инициализирующий матрицу некоторой заранее заданной
  // размерностью
  S21Matrix();
  // Параметризированный конструктор с количеством строк и столбцов
  S21Matrix(int rows, int cols);
  // Конструктор копирования
  S21Matrix(const S21Matrix &other);
  // Конструктор переноса
  S21Matrix(S21Matrix &&other);
  // Деструктор
  ~S21Matrix();

  // Прибавляет вторую матрицы к текущей
  void SumMatrix(const S21Matrix &other);
  // Проверяет матрицы на равенство между собой
  bool EqMatrix(const S21Matrix &other);
  // Вычитает из текущей матрицы другую
  void SubMatrix(const S21Matrix &other);
  // Умножает текущую матрицу на число
  void MulNumber(const double num);
  // Умножает текущую матрицу на вторую
  void MulMatrix(const S21Matrix &other);
  // Создает новую транспонированную матрицу из текущей и возвращает ее
  S21Matrix Transpose();
  // Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее
  S21Matrix CalcComplements();
  // Вычисляет и возвращает определитель текущей матрицы
  double Determinant();
  // Вычисляет и возвращает обратную матрицу
  S21Matrix InverseMatrix();

  // Сложение двух матриц
  S21Matrix operator+(const S21Matrix &other);
  // Вычитание одной матрицы из другой
  S21Matrix operator-(const S21Matrix &other);
  // Умножение матриц
  S21Matrix operator*(const S21Matrix &other);
  // Умножение матрицы на число
  S21Matrix operator*(const double num);
  // Проверка на равенство матриц
  bool operator==(const S21Matrix &other);
  // Присвоение матрице значений другой матрицы
  S21Matrix &operator=(const S21Matrix &other);
  // Присвоение сложения (`SumMatrix`)
  void operator+=(const S21Matrix &other);
  // Присвоение разности (`SubMatrix`)
  void operator-=(const S21Matrix &other);
  // Присвоение умножения (`MulMatrix`)
  void operator*=(const S21Matrix &other);
  // Присвоение умножения (`MulNumber`)
  void operator*=(const double num);
  // Индексация по элементам матрицы
  double &operator()(int i, int j);

  S21Matrix GetMinor(int row, int col);

  // accesors
  double GetMatrixMember(int row, int col);
  int GetRows();
  int GetCols();

  // mutators
  void SetMatrixMember(int row, int col, double value);
  void SetRows(int value);
  void SetCols(int value);

  // etc
  void AllocateMatrix();
};

#endif
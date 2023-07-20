#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw "Invalid matrix size";
  }
  rows_ = rows;
  cols_ = cols;
  AllocateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  AllocateMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  AllocateMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  other.~S21Matrix();
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw "Wrong matrix size";
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool is_equal = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    is_equal = false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-6) {
          is_equal = false;
        }
      }
    }
  }
  return is_equal;
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw "Wrong matrix size";
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_ || rows_ != other.cols_) {
    throw "Wrong size";
  }
  S21Matrix temp(*this);
  this->~S21Matrix();
  rows_ = temp.rows_;
  cols_ = other.cols_;
  AllocateMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      double value = 0;
      for (int k = 0; k < temp.cols_; k++) {
        value += temp.matrix_[i][k] * other.matrix_[k][j];
      }
      matrix_[i][j] = value;
    }
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw "Matrix not square";
  }
  S21Matrix result(rows_, cols_);
  if (result.rows_ == 1) {
    if (fabs(matrix_[0][0] < 1e-6)) {
      throw "Can't calculate complements for this matrix";
    } else {
      result.matrix_[0][0] = 1;
    }
  } else {
    for (int i = 0; i < result.rows_; i++) {
      for (int j = 0; j < result.cols_; j++) {
        double determinant;
        S21Matrix temp(GetMinor(i + 1, j + 1));
        determinant = temp.Determinant();
        result.matrix_[i][j] = pow((-1), i + j) * determinant;
      }
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw "Matrix not square";
  }
  double result = 0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    S21Matrix temp(rows_ - 1, cols_ - 1);
    for (int i = 0; i < cols_; i++) {
      for (int j = 0; j < temp.rows_; j++) {
        for (int k = 0; k < i; k++) {
          temp.matrix_[j][k] = matrix_[j + 1][k];
        }
        for (int k = i; k < temp.cols_; k++) {
          temp.matrix_[j][k] = matrix_[j + 1][k + 1];
        }
      }
      double other_det = temp.Determinant();
      result += matrix_[0][i] * pow(-1, i + 2) * other_det;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  double determinant = Determinant();
  if (determinant == 0) {
    throw "Null determinant";
  }
  S21Matrix result(rows_, cols_);
  S21Matrix temp(CalcComplements());
  S21Matrix transposed(temp.Transpose());
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.matrix_[i][j] = transposed.matrix_[i][j] / determinant;
    }
  }
  return result;
}

S21Matrix S21Matrix::GetMinor(int row, int col) {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  int m, n;
  for (int i = 0; i < rows_; i++) {
    m = i;
    if (i > row - 1) {
      m--;
    }
    for (int j = 0; j < rows_; j++) {
      n = j;
      if (j > col - 1) {
        n--;
      }
      if (i != row - 1 && j != col - 1) {
        minor.matrix_[m][n] = matrix_[i][j];
      }
    }
  }
  return minor;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  this->~S21Matrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  AllocateMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

void S21Matrix::operator+=(const S21Matrix &other) { SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix &other) { SubMatrix(other); }

void S21Matrix::operator*=(const S21Matrix &other) { MulMatrix(other); }

void S21Matrix::operator*=(const double num) { this->MulNumber(num); }

double &S21Matrix::operator()(int i, int j) {
  if (i < 0 || i > this->rows_ - 1 || j < 0 || j > cols_ - 1) {
    throw "Index out of range";
  }
  return matrix_[i][j];
}

double S21Matrix::GetMatrixMember(int row, int col) {
  return matrix_[row][col];
}

int S21Matrix::GetRows() { return rows_; }

int S21Matrix::GetCols() { return cols_; }

void S21Matrix::SetMatrixMember(int row, int col, double value) {
  matrix_[row][col] = value;
}

void S21Matrix::SetRows(int value) { rows_ = value; }

void S21Matrix::SetCols(int value) { cols_ = value; }

void S21Matrix::AllocateMatrix() {
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}
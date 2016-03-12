#include "matrix.hpp"

matrix::matrix() {
  this->row = 1;
  this->col = 1;
}

// Asumption ; row * col == sizeof(array); not save function
matrix::matrix(int row, int col, double array[]){

  assert(row > 0 && col > 0);

  this->row = row;
  this->col = col;

  this->container.resize(row);
  for (int i = 0; i < row; i++) {
    this->container[i].resize(col);
  }

  int it = 0;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      this->container[i][j] = array[it];
      it++;
    }
  }
}

// Getter
int matrix::get_row() {
  return row;
}

int matrix::get_col() {
  return col;
}

std::vector<std::vector<double> > matrix::get_container() {
  return container;
}

double matrix::at(int i, int j) {
  assert(i < row && j < col);

  return container[i][j];
}

// Setter
void matrix::set_row(int new_row) {
  this->row = new_row;
}

void matrix::set_col(int new_col) {
  this->col = new_col;
}

void matrix::set_container(std::vector<std::vector<double> > vector2d) {
  this->container = vector2d;
}

matrix matrix::multiplication(matrix& A, matrix& B){

  int row_A = A.get_row();
  int col_A = A.get_col();
  int row_B = B.get_row();
  int col_B = B.get_col();
  assert(col_A == row_B); // assert col A == row B

  double result[row_A * col_B];

  // matrix A x matrix B
  int it;
  for (int i = 0; i < row_A; i++) {
    for (int j = 0; j < col_B; j++) {
      result[it] = 0;
      for (int k = 0; k < col_A; k++) {
        result[it] += A.at(i,k) * B.at(k,j);
      }
      it++;
    }
  }

  return matrix(row_A, col_B, result);
}

void matrix::print() {

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      std::cout << container[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

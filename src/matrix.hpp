/*
 * This class have responsibility to handle matrix operation
 */

#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <cassert>
#include <iostream>

class matrix {

public:

  /*
   * Default constructor
   */
  matrix();

  /*
   * matrix constructor will convert one dimensional array to 2d array with row x col
   * row major ordering
   */
  matrix(int row, int col, double array[]);

  // Getter
  int get_row();
  int get_col();
  std::vector<std::vector<double> > get_container();
  double at(int i, int j);

  // Setter
  void set_row(int new_row);
  void set_col(int new_col);
  void set_container(std::vector<std::vector<double> > vector2d);

  /*
   * input vector 2D type double; m x n and n x p
   * output vector 2D type double; m x p
   */
  static matrix multiplication(matrix& A, matrix& B);

  void print();

private:
  int row;
  int col;
  std::vector<std::vector<double> > container;
};

#endif

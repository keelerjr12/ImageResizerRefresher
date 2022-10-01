#ifndef MATRIX_H
#define MATRIX_H

/* Matrix.h
 * Project UID af1f95f547e44c8ea88730dfb185559d
 * Originally written by James Juett at the University of Michigan
 * for project 3 in EECS 280, Winter 2016.
 */

#include <iostream>
#include <vector>

const int MAX_MATRIX_WIDTH = 500;
const int MAX_MATRIX_HEIGHT = 500;

// Representation of a 2D matrix of integers
// Matrix objects may be copied.
class Matrix{

 public:
     
  // EFFECTS:  Initializes this as a Matrix with the given width and height.
  Matrix(int width, int height);

  // EFFECTS:  this as a Matrix with the given width and height.
  Matrix(const Matrix& rhs);
  
  // EFFECTS:  Returns the width of the Matrix.
  int get_width() const { return width; }
  
  // EFFECTS:  Returns the height of the Matrix.
  int get_height() const { return height; }

  // REQUIRES: 0 <= row && row < mat->get_height()
  //           0 <= column && column < mat->get_width()
  // MODIFIES: (The returned reference may be used to modify an
  //            element in the Matrix.)
  // EFFECTS:  Returns a reference to the element in the Matrix
  //           at the given row and column.
  int& at(int row, int column);
  const int& at(int row, int column) const;
  
  std::vector<int>::iterator begin() { return data.begin(); } 
  std::vector<int>::iterator end() { return data.end(); } 
  std::vector<int>::const_iterator cbegin() const { return data.cbegin(); } 
  std::vector<int>::const_iterator cend() const { return data.cend(); } 
  
  // MODIFIES: Data vector
  // EFFECTS:  Sets each element of the Matrix to the given value.
  void fill(int value);
  
  // MODIFIES: Data vector
  // EFFECTS:  Sets each element on the border of the Matrix to
  //           the given value. These are all elements in the first/last
  //           row or the first/last column.
  void fill_border(int value);

 private:
  int width;
  int height;

 public:
  std::vector<int> data;
};


// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix& mat, std::ostream& os);


// REQUIRES: ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix& mat, const int* ptr);


// REQUIRES: mat points to a valid Matrix
//           tr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix& mat, const int* ptr);


// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix& mat);

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < mat->get_height()
//           0 <= column_start && column_end <= mat->get_width()
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix& mat, int row,
                                      int column_start, int column_end);

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < mat->get_height()
//           0 <= column_start && column_end <= mat->get_width()
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix& mat, int row,
                            int column_start, int column_end);

#endif // MATRIX_H

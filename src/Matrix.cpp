// Project UID af1f95f547e44c8ea88730dfb185559d
#include "Matrix.h"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <limits>
#include <memory>

bool in_bounds(const Matrix& mat, int row, int col);

/********** Matrix ********
 *
 */

// EFFECTS:  Initializes this as a Matrix with the given width and height.
Matrix::Matrix(int width, int height) : width(width), height(height), 
    data(width * height, 0) { }

// EFFECTS:  Initializes this as a Matrix by copying the input matrix
Matrix::Matrix(const Matrix& rhs) : width(rhs.width), height(rhs.height),
    data(rhs.data) { }

// REQUIRES: 0 <= row && row < mat->get_height()
//           0 <= column && column < mat->get_width()
// MODIFIES: (The returned reference may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a reference to the element in the Matrix
//           at the given row and column.
int& Matrix::at(int row, int column) {
  assert(in_bounds(*this, row, column));

  return data[row * get_width() + column];
}

const int& Matrix::at(int row, int column) const {
  assert(in_bounds(*this, row, column));
  
  return data[row * get_width() + column];
}

// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix::row_index(const int& el) const {
    return (&el - &data[0]) / get_width();
}

// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix::col_index(const int& el) const {
    return (&el - &data[0]) % get_width();
}

// MODIFIES: Data vector
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix::fill_border(int value) {
    // Fill top * bottoms rows
    for (auto c = 0; c < get_width(); ++c) {
        at(0, c) = value;
        at(get_height() - 1, c) = value;
    }
    
    // Fill left & right columns
    for (auto r = 0; r < get_height(); ++r) {
        at(r, 0) = value;
        at(r, get_width() - 1) = value;
    }
}


/********** Matrix::RowVecIterator ********
 *
 */

Matrix::RowVecIterator::RowVecIterator(const Matrix& mat, int row, int col) : mat(&mat), row(row), col(col) { }

Matrix::RowVecIterator& Matrix::RowVecIterator::operator+=(Matrix::RowVecIterator::difference_type n) {
  this->col += n;
  return *this;
}

Matrix::RowVecIterator& Matrix::RowVecIterator::operator++() {
  ++col;
  return *this;
}

Matrix::RowVecIterator Matrix::RowVecIterator::operator++(int) {
  auto tmp = *this;
  ++(*this);
  return tmp;
}

Matrix::RowVecIterator::reference Matrix::RowVecIterator::operator*() {
  return mat->at(row, col);
}
bool operator==(const Matrix::RowVecIterator& lhs, const Matrix::RowVecIterator& rhs) {
  return (lhs.mat == rhs.mat) && (lhs.row == rhs.row) && (lhs.col == rhs.col);
}

bool operator!=(const Matrix::RowVecIterator& lhs, const Matrix::RowVecIterator& rhs) {
  return !(lhs == rhs);
}

/********** Matrix::RowIterator ********
 *
 */

Matrix::RowIterator::RowIterator(const Matrix& mat, int row) : mat(mat), row(row), col(0) { }

Matrix::RowIterator& Matrix::RowIterator::operator++() {
  ++row;
  return *this;
}

Matrix::RowIterator Matrix::RowIterator::operator++(int) {
  auto tmp = *this;
  ++(*this);
  return tmp;
}

Matrix::RowIterator::value_type Matrix::RowIterator::operator*() const {
  return RowVecIterator(mat, row, col);
}

bool operator==(const Matrix::row_iterator& lhs, const Matrix::row_iterator& rhs) {
  return (lhs.mat == rhs.mat) && (lhs.row == rhs.row) && (lhs.col == rhs.col);
}

bool operator!=(const Matrix::row_iterator& lhs, const Matrix::row_iterator& rhs) {
  return !(lhs == rhs);
}

/********** Matrix cont. ********
 *
 */

Matrix::row_iterator Matrix::row_begin(int row_index) {
  return row_iterator(*this, row_index);
}

Matrix::row_iterator Matrix::row_end() { 
  return row_iterator(*this, get_height());
}

Matrix::const_row_iterator Matrix::row_cbegin(int row_index) const {
  return const_row_iterator(*this, row_index);
}

Matrix::const_row_iterator Matrix::row_cend() const { 
  return const_row_iterator(*this, get_height());
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
  return lhs.data == rhs.data;
}

bool operator!=(const Matrix& lhs, const Matrix& rhs) {
  return !(lhs == rhs);
}

Matrix::RowVecIterator operator+(const Matrix::RowVecIterator& x, Matrix::RowVecIterator::difference_type n) {
  Matrix::RowVecIterator tmp(x);
  tmp  += n;
  return tmp;
}
// MODIFIES: Matrix mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix& mat, int value) {
  std::fill(std::begin(mat), std::end(mat), value);
}

// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix& mat, std::ostream& os) {
  os << mat.get_width() << " " <<  mat.get_height() << std::endl;

  for (auto row = mat.row_cbegin(0); row != mat.row_cend(); ++row) {
    for (auto el : *row) {
      std::cout << el << ' ';
    }

    std::cout << '\n';
  }
}

// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix& mat) {
  return *std::max_element(mat.cbegin(), mat.cend());
}

// REQUIRES: 0 <= row && row < mat->get_height()
//           0 <= column_start && column_end <= mat->get_width()
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix& mat, int row,
                                      int column_start, int column_end) {
  assert(in_bounds(mat, row, column_start));
  assert(in_bounds(mat, row, column_end-1));
  assert(column_start < column_end);

  auto row_it = mat.row_cbegin(row);
  auto min_el = std::min_element((*row_it).cbegin() + column_start, (*row_it).cend());
  auto min_el_idx = std::distance((*row_it).cbegin(), min_el);

  return min_el_idx;
}

// REQUIRES: 0 <= row && row < mat->get_height()
//           0 <= column_start && column_end <= mat->get_width()
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix& mat, int row,
                            int column_start, int column_end) {
    assert(0 <= row && row < mat.get_height());
    assert(0 <= column_start && column_end <= mat.get_width());
    assert(column_start < column_end);
    
    auto min_col = Matrix_column_of_min_value_in_row(mat, row, column_start, column_end);

    return mat.at(row, min_col);
}

bool in_bounds(const Matrix& mat, int row, int col) {
  if (row < 0 || row >= mat.get_height())
    return false;

  if (col < 0 || col >= mat.get_width())
    return false;

  return true;
} 

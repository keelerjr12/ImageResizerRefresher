// Project UID af1f95f547e44c8ea88730dfb185559d
#include "Matrix.h"
#include <cassert>
#include <iterator>
#include <limits>
#include <memory>

/********** Matrix ********
 *
 */

// EFFECTS:  Initializes this as a Matrix with the given width and height.
Matrix::Matrix(int width, int height) : width(width), height(height), 
    data(width * height) {

  fill(0);
}

// EFFECTS:  this as a Matrix with the given width and height.
Matrix::Matrix(const Matrix& rhs) : width(rhs.width), height(rhs.height),
    data(rhs.data) {
}

// REQUIRES: 0 <= row && row < mat->get_height()
//           0 <= column && column < mat->get_width()
// MODIFIES: (The returned reference may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a reference to the element in the Matrix
//           at the given row and column.
int& Matrix::at(int row, int column) {
  assert(0 <= row && row <= get_height());
  assert(0 <= column && column <= get_width());

  return data[row * get_width() + column];
}

const int& Matrix::at(int row, int column) const {
  assert(0 <= row && row <= get_height());
  assert(0 <= column && column <= get_width());
  
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
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix::fill(int value) {
  for (auto &el : data)
  {
    el = value;
  }
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

Matrix::RowVecIterator::RowVecIterator(Matrix& mat, int row, int col) : mat(mat), row(row), col(col) { }

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
  return mat.at(row, col);
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

Matrix::row_iterator Matrix::row_end() { // TODO: change this to take in a row_index ofw here to end
  return row_iterator(*this, get_height());
}

Matrix::const_row_iterator Matrix::row_cbegin(int row_index) const {
  return const_row_iterator(*this, row_index);
}

Matrix::const_row_iterator Matrix::row_cend() const { // TODO: change this to take in a row_index ofw here to end
  return const_row_iterator(*this, get_height());
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
  return lhs.data == rhs.data;
}

bool operator!=(const Matrix& lhs, const Matrix& rhs) {
  return !(lhs == rhs);
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
    auto max = std::numeric_limits<int>::min();

    for (auto it = mat.cbegin(); it != mat.cend(); ++it) {
      if (max < *it) {
        max = *it;
      }
    }

    return max;
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
    assert(0 <= row && row < mat.get_height());
    assert(0 <= column_start && column_end <= mat.get_width());
    assert(column_start < column_end);
    
    auto min = mat.at(row, column_start);
    auto min_c = column_start;

    for (auto c = column_start + 1; c < column_end; ++c) {
       auto val = mat.at(row, c);
       
       if (val < min) {
           min = val;
           min_c = c;
       }
    }

    return min_c;
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
    
    auto min = mat.at(row, column_start);

    for (auto c = column_start + 1; c < column_end; ++c) {
       auto val = mat.at(row, c);
       
       if (val < min) {
           min = val;
       }
    }

    return min;
}

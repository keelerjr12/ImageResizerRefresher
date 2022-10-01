// Project UID af1f95f547e44c8ea88730dfb185559d
#include "Matrix.h"
#include <cassert>
#include <iterator>
#include <limits>
#include <memory>

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
Matrix::Matrix(int width, int height) 
  : data(MAX_MATRIX_WIDTH * MAX_MATRIX_HEIGHT) {

  assert(0 < width && width <= MAX_MATRIX_WIDTH);
  assert(0 < height && height <= MAX_MATRIX_HEIGHT);

  this->width = width;
  this->height = height;

  fill(0);
}

Matrix::Matrix(const Matrix& rhs) : width(rhs.width),
    height(rhs.height), data(rhs.data) {
}

// REQUIRES: 0 <= row && row < mat->get_height()
//           0 <= column && column < mat->get_width()
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
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

// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix::fill(int value) {
  for (auto r = 0; r < get_height(); ++r) {
    for (auto c = 0; c < get_width(); ++c) {
      at(r, c) = value;
    }
  }
}

// MODIFIES: *mat
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

// REQUIRES: 
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix& mat, std::ostream& os) {
  os << mat.get_width() << " " <<  mat.get_height() << std::endl;

  for (auto r = 0; r < mat.get_height(); ++r) {
    for (auto c = 0; c < mat.get_width(); ++c) {
      os << mat.at(r, c) << " ";
    }

    os << std::endl;
  }
}

// REQUIRES: ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix& mat, const int* ptr) {
    return (ptr - &mat.data[0]) / mat.get_width();
}

// REQUIRES: ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix& mat, const int* ptr) {
    return (ptr - &mat.data[0]) % mat.get_width();
}


// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix& mat) {
    auto max = std::numeric_limits<int>::min();

    for (auto r = 0; r < mat.get_height(); ++r) {
        for (auto c = 0; c < mat.get_width(); ++c) {
            auto curr_val = mat.at(r, c);
            
            if (max < curr_val) {
                max = curr_val;
            }
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

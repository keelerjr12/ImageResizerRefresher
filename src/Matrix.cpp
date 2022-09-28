// Project UID af1f95f547e44c8ea88730dfb185559d
#include <cassert>
#include <limits>
#include "Matrix.h"

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
Matrix::Matrix(int width, int height) {
    assert(0 < width && width <= MAX_MATRIX_WIDTH);
    assert(0 < height && height <= MAX_MATRIX_HEIGHT);

    this->width = width;
    this->height = height;

    Matrix_fill(this, 0);
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
    assert(mat);

    os << mat->get_width() << " " <<  mat->get_height() << std::endl;

    for (auto r = 0; r < mat->get_height(); ++r) {
        for (auto c = 0; c < mat->get_width(); ++c) {
            os << *Matrix_at(mat, r, c) << " ";
        }

        os << std::endl;
    }
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
    assert(mat);
    assert(ptr >= mat->data &&
          (mat->data + (mat->get_width() * mat->get_height()) - 1));

    return (ptr - mat->data) / mat->get_width();
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
    assert(mat);
    assert(ptr >= mat->data &&
          (mat->data + (mat->get_width() * mat->get_height()) - 1));

    return (ptr - mat->data) % mat->get_width();
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < mat->get_height()
//           0 <= column && column < mat->get_width()
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
    assert(mat);
    assert(0 <= row && row <= mat->get_height());
    assert(0 <= column && column <= mat->get_width());

    return &mat->data[row * mat->get_width() + column];
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < mat->get_height()
//           0 <= column && column < mat->get_width()
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
    assert(mat);
    assert(0 <= row && row <= mat->get_height());
    assert(0 <= column && column <= mat->get_width());

    return &mat->data[row * mat->get_width() + column];
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
    assert(mat);

    for (auto r = 0; r < mat->get_height(); ++r) {
        for (auto c = 0; c < mat->get_width(); ++c) {
            *Matrix_at(mat, r, c) = value;
        }
    }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
    assert(mat);

    // Fill top * bottoms rows
    for (auto c = 0; c < mat->get_width(); ++c) {
        *Matrix_at(mat, 0, c) = value;
        *Matrix_at(mat, mat->get_height() - 1, c) = value;
    }
    
    // Fill left & right columns
    for (auto r = 0; r < mat->get_height(); ++r) {
        *Matrix_at(mat, r, 0) = value;
        *Matrix_at(mat, r, mat->get_width() - 1) = value;
    }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
    assert(mat);

    auto max = std::numeric_limits<int>::min();

    for (auto r = 0; r < mat->get_height(); ++r) {
        for (auto c = 0; c < mat->get_width(); ++c) {
            auto curr_val = *Matrix_at(mat, r, c);
            
            if (max < curr_val) {
                max = curr_val;
            }
        }
    }

    return max;
}

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
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
    assert(mat);
    assert(0 <= row && row < mat->get_height());
    assert(0 <= column_start && column_end <= mat->get_width());
    assert(column_start < column_end);
    
    auto min = *Matrix_at(mat, row, column_start);
    auto min_c = column_start;

    for (auto c = column_start + 1; c < column_end; ++c) {
       auto val = *Matrix_at(mat, row, c);
       
       if (val < min) {
           min = val;
           min_c = c;
       }
    }

    return min_c;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < mat->get_height()
//           0 <= column_start && column_end <= mat->get_width()
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
    assert(mat);
    assert(0 <= row && row < mat->get_height());
    assert(0 <= column_start && column_end <= mat->get_width());
    assert(column_start < column_end);
    
    auto min = *Matrix_at(mat, row, column_start);

    for (auto c = column_start + 1; c < column_end; ++c) {
       auto val = *Matrix_at(mat, row, c);
       
       if (val < min) {
           min = val;
       }
    }

    return min;
}

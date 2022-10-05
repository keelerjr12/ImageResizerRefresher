// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <cstring>
#include <sstream>

using namespace std;
using namespace MatrixNS;

// Fills a 3x5 Matrix with a value and checks
// that at returns that value for each element.
TEST(test_fill_basic) {
  const int width = 3;
  const int height = 5;
  const int value = 42;

  auto mat = Matrix(3, 5);
  fill(mat, value);

  for(int r = 0; r < height; ++r) {
    for(int c = 0; c < width; ++c) {
      ASSERT_EQUAL(mat.at(r, c), value);
    }
  }
}

// 
TEST(ones_matrix_print) {
  auto CORRECT_STR = "2 3\n1 1 \n1 1 \n1 1 \n";

  const auto width = 2;
  const auto height = 3;

  auto mat = Matrix(width, height);

  const auto value = 1;
  fill(mat, value);

  std::ostringstream os;
  print(mat, os);
  
  auto is_equal = (os.str() == CORRECT_STR);
  ASSERT_EQUAL(is_equal, true);
}

// Initialize matrix and query the given width
TEST(init_matrix_query_width) {
  const int width = 3;
  const int height = 5;

  auto mat = Matrix(width, height);

  ASSERT_EQUAL(mat.get_width(), width);
}

// Initialize matrix and query the given height
TEST(init_matrix_query_height) {
  const int width = 3;
  const int height = 5;

  auto mat = Matrix(width, height);

  ASSERT_EQUAL(mat.get_height(), height);
}

// Return first row of specified element
TEST(filled_matrix_element_first_row_return_first_row) {
  const int width = 3;
  const int height = 5;
  
  auto mat = Matrix(width, height);
  fill(mat, 5);
  auto el = &mat.at(0, 0);

  ASSERT_EQUAL(mat.row_index(*el), 0);
}

// Return last row of specified element
TEST(filled_matrix_element_last_row_return_last_row) {
  const int width = 3;
  const int height = 5;
  
  auto mat = Matrix(width, height);
  fill(mat, 5);
  auto el = &mat.at(height-1, 0);

  ASSERT_EQUAL(mat.row_index(*el), height-1);
}

// Return first column of specified element
TEST(filled_matrix_element_first_column_return_first_column) {
  const int width = 3;
  const int height = 5;
  
  auto mat = Matrix(width, height);
  fill(mat, 5);
  auto el = &mat.at(0, 0);

  ASSERT_EQUAL(mat.col_index(*el), 0);
}

// Return last column of specified element
TEST(filled_matrix_element_last_column_return_last_column) {
  const int width = 3;
  const int height = 5;
  
  auto mat = Matrix(width, height);
  fill(mat, 5);
  auto el = &mat.at(height-1, width-1);

  ASSERT_EQUAL(mat.col_index(*el), width-1);
}

// Verify that at changes value 
TEST(filled_matrix_changing_value_returns_changed_value) {
  const int width = 3;
  const int height = 5;
  const int changed_val = 3;
  
  auto mat = Matrix(width, height);
  fill(mat, 5);
  mat.at(height-1, width-1) = changed_val;

  ASSERT_EQUAL(mat.at(height-1, width-1), changed_val);
}

// Check that border was filled
TEST(filled_matrix_fill_border) {
  const int width = 3;
  const int height = 4;
  const int value = 2;
  
  auto mat = Matrix(width, height);
  mat.fill_border(value);

  auto correct_mat = Matrix(width, height);

  // top border
  for (auto col = 0; col < width; ++col) {
    correct_mat.at(0, col) = value;
  }
    
  // left border
  for (auto row = 0; row < height; ++row) {
    correct_mat.at(row, 0) = value;
  }

  // right border
  for (auto row = 0; row < height; ++row) {
    correct_mat.at(row, width-1) = value;
  }

  // bottom border
  for (auto col = 0; col < width; ++col) {
    correct_mat.at(height-1, col) = value;
  }

  ASSERT_EQUAL(Matrix_equal(mat, correct_mat), true);
}

// Return max value
TEST(filled_matrix_return_max_element) {
  const int width = 3;
  const int height = 5;
  
  auto mat = Matrix(width, height);
  fill(mat, 5);

  mat.at(height/2, width/2) = 10;
  mat.at(0, width-1) = 40;
  mat.at(height-1, 0) = 30;
  mat.at(height-1, width-1) = 20;

  
  ASSERT_EQUAL(max(mat), 40);
}

// Get column when min value in column start
TEST(min_val_start_return_start_col) {
  const int width = 8;
  const int height = 5;
  
  auto mat = Matrix(width, height);
  fill(mat, 5);

  // fill 1st row with increasing ints
  for (auto c = 0; c < width; ++c) {
    mat.at(0, c) = c;
  }

  // skip 1st col and report min col as 2nd col
  auto min_col = column_of_min_value_in_row(mat, 0, 1, width-1);
  
  ASSERT_EQUAL(min_col, 1);
}

// Get column of min value when decreasing order of last row 
TEST(min_val_start_return_last_col) {
  const int width = 8;
  const int height = 5;
  
  auto mat = Matrix(width, height);
  fill(mat, 5);

  // fill last row with decreasing ints
  for (auto c = 0; c < width; ++c) {
    mat.at(height-1, c) = width - c;
  }

  // get min_col as last col 
  auto min_col = column_of_min_value_in_row(mat, height-1, 0, width);
  
  ASSERT_EQUAL(min_col, width-1);
}

// Get min value when in column start
TEST(min_val_start_return_min_val_in_start_col) {
  const int width = 8;
  const int height = 5;
  
  auto mat = Matrix(width, height);
  fill(mat, 5);

  // fill 1st row with increasing ints
  for (auto c = 0; c < width; ++c) {
    mat.at(0, c) = c;
  }

  // skip 1st col and report min col as 2nd col
  auto min = min_value_in_row(mat, 0, 1, width-1);
  
  ASSERT_EQUAL(min, 1);
}

// Get min value when decreasing order of last row 
TEST(min_val_start_return_last_col_val) {
  const int width = 8;
  const int height = 5;
  
  auto mat = Matrix(width, height);
  fill(mat, 5);

  // fill last row with decreasing ints
  for (auto c = 0; c < width; ++c) {
    mat.at(height-1, c) = width - c;
  }

  // get min_col as last col 
  auto min = min_value_in_row(mat, height-1, 0, width);
  
  ASSERT_EQUAL(min, 1);
}

TEST_MAIN() // Do NOT put a semicolon here

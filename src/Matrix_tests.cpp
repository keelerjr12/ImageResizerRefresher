// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <cstring>
#include <sstream>

using namespace std;

// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// 
// 
TEST(ones_matrix_print) {
    auto CORRECT_STR = "2 3\n1 1 \n1 1 \n1 1 \n";

    const int width = 2;
    const int height = 3;
    const int value = 1;

    Matrix *mat = new Matrix; // create a Matrix in dynamic memory
    Matrix_init(mat, width, height);
    Matrix_fill(mat, value);

    std::ostringstream os;
    Matrix_print(mat, os);

    auto is_equal =  strncmp(os.str().c_str(), CORRECT_STR, os.str().size());

    ASSERT_EQUAL(is_equal, 0);

    delete mat; // delete the Matrix
}

// Initialize matrix and query the given width
TEST(init_matrix_query_width) {
  Matrix *mat = new Matrix; 
  const int width = 3;
  const int height = 5;

  Matrix_init(mat, width, height);

  ASSERT_EQUAL(Matrix_width(mat), width);
  delete mat;
}

// Initialize matrix and query the given height
TEST(init_matrix_query_height) {
  Matrix *mat = new Matrix; 
  const int width = 3;
  const int height = 5;

  Matrix_init(mat, width, height);

  ASSERT_EQUAL(Matrix_height(mat), height);
  delete mat;
}

// Return first row of specified element
TEST(filled_matrix_element_first_row_return_first_row) {
    Matrix *mat = new Matrix; 
    const int width = 3;
    const int height = 5;
  
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 5);
    auto el = Matrix_at(mat, 0, 0);

    ASSERT_EQUAL(Matrix_row(mat, el), 0);
    delete mat;
}

// Return last row of specified element
TEST(filled_matrix_element_last_row_return_last_row) {
    Matrix *mat = new Matrix; 
    const int width = 3;
    const int height = 5;
  
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 5);
    auto el = Matrix_at(mat, height-1, 0);

    ASSERT_EQUAL(Matrix_row(mat, el), height-1);
    delete mat;
}

// Return first column of specified element
TEST(filled_matrix_element_first_column_return_first_column) {
    Matrix *mat = new Matrix; 
    const int width = 3;
    const int height = 5;
  
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 5);
    auto el = Matrix_at(mat, 0, 0);

    ASSERT_EQUAL(Matrix_column(mat, el), 0);
    delete mat;
}

// Return last column of specified element
TEST(filled_matrix_element_last_column_return_last_column) {
    Matrix *mat = new Matrix; 
    const int width = 3;
    const int height = 5;
  
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 5);
    auto el = Matrix_at(mat, height-1, width-1);

    ASSERT_EQUAL(Matrix_column(mat, el), width-1);
    delete mat;
}

// Verify that Matrix_at changes value 
TEST(filled_matrix_changing_value_returns_changed_value) {
    Matrix *mat = new Matrix; 
    const int width = 3;
    const int height = 5;
    const int value = 2;
    const int changed_val = 3;
  
    Matrix_init(mat, width, height);
    Matrix_fill(mat, value);
    *Matrix_at(mat, height-1, width-1) = changed_val;

    ASSERT_EQUAL(*Matrix_at(mat, height-1, width-1), changed_val);
    delete mat;
}

// Check that border was filled
TEST(filled_matrix_fill_border) {
    const int width = 3;
    const int height = 4;
    const int value = 2;
  
    Matrix *mat = new Matrix; 
    Matrix_init(mat, width, height);
    Matrix_fill_border(mat, value);

    Matrix *correct_mat = new Matrix;
    Matrix_init(correct_mat, width, height);

    // top border
    for (auto col = 0; col < width; ++col) {
        *Matrix_at(correct_mat, 0, col) = value;
    }
        
    // left border
    for (auto row = 0; row < height; ++row) {
        *Matrix_at(correct_mat, row, 0) = value;
    }

    // right border
    for (auto row = 0; row < height; ++row) {
        *Matrix_at(correct_mat, row, width-1) = value;
    }

    // bottom border
    for (auto col = 0; col < width; ++col) {
        *Matrix_at(correct_mat, height-1, col) = value;
    }

    ASSERT_EQUAL(Matrix_equal(mat, correct_mat), true);

    delete mat;
}

// Return max value
TEST(filled_matrix_return_max_element) {
    Matrix *mat = new Matrix; 
    const int width = 3;
    const int height = 5;
  
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 5);

    *Matrix_at(mat, height/2, width/2) = 10;
    *Matrix_at(mat, 0, width-1) = 40;
    *Matrix_at(mat, height-1, 0) = 30;
    *Matrix_at(mat, height-1, width-1) = 20;

    
    ASSERT_EQUAL(Matrix_max(mat), 40);
    delete mat;
}

TEST_MAIN() // Do NOT put a semicolon here

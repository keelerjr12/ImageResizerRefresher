// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

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

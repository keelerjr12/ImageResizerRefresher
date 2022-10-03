// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <sstream>

using std::ostringstream;


// This is the public Matrix test for which the autograder gives feedback.
// It only tests VERY FEW of the expected behaviors of the Matrix module.
// It will only really tell you if your code compiles and you remembered to
// write the functions. It is not to be trusted. It tells the truth, but not
// the whole truth. It might put you in a blender. You get the point.
// You must write your own comprehensive unit tests in Matrix_tests.cpp!


TEST(test_matrix_basic) {
  auto mat = Matrix(5, 5);

  ASSERT_EQUAL(mat.get_width(), 5);
  ASSERT_EQUAL(mat.get_height(), 5);

  mat.fill(0);

  int *ptr = &mat.at(2, 3);
  ASSERT_EQUAL(mat.row_index(*ptr), 2);
  ASSERT_EQUAL(mat.col_index(*ptr), 3);
  ASSERT_EQUAL(*ptr, 0);
  *ptr = 42;

  const int *cptr = &mat.at(2, 3);
  ASSERT_EQUAL(*cptr, 42);

  mat.fill_border(2);
  ASSERT_EQUAL(mat.at(0, 0), 2);

  ASSERT_EQUAL(Matrix_max(mat), 42);
}

TEST(test_matrix_print) {
  auto mat = Matrix(1, 1);

  mat.at(0, 0) = 42;
  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
}

TEST_MAIN()

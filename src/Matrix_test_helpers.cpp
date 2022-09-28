
/* Matrix_test_helpers.cpp
 * Project UID af1f95f547e44c8ea88730dfb185559d
 * Originally written by James Juett at the University of Michigan
 * for project 3 in EECS 280, Winter 2016.
 */

#include "Matrix_test_helpers.h"

bool Matrix_equal(const Matrix* mat1, const Matrix* mat2){
  if (mat1->get_width() != mat2->get_width()){ return false; }
  if (mat1->get_height() != mat2->get_height()){ return false; }

  for(int r = 0; r < mat1->get_height(); ++r){
    for(int c = 0; c < mat1->get_width(); ++c){
      if (*Matrix_at(mat1, r, c) != *Matrix_at(mat2, r, c)){ return false; }
    }
  }
  
  return true;
}

bool array_equal(const int arr1[], const int arr2[], int n){
  for(int i = 0; i < n; ++i){
    if(arr1[i] != arr2[i]){ return false; }
  }

  return true;
}


#include <iostream>
#include "Matrix.h"

int main() {
  auto mat = Matrix(5, 5);
  mat.fill(10);

//  for (Matrix::RowIterator it = mat.row_begin(1); it != mat.row_end(); ++it) {
//    for (auto vit = (*it).begin(); vit != (*it).end(); ++vit) {
//      std::cout << *vit << " ";
//    }
//
//    std::cout << std::endl;
//  }
  
//  auto row_begin = mat.row_begin(0);
//  auto row_end = mat.row_end();
//  auto row_it = row_begin;

//  for (; row_it != row_end; ++row_it) {
//    for (auto rvit = (*row_it).begin(); rvit != (*row_it).end(); ++rvit) {
//      std::cout << *rvit << " ";
//    }
//
//    std::cout << std::endl;
//  }

  mat.at(2, 4) = 333;

  for (auto row = mat.row_begin(0); row != mat.row_end(); ++row) {
    for (auto el : *row) {
      std::cout << el << ' ';
    }

    std::cout << '\n';
  }

  return 0;
}

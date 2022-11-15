#include "Matrix.h"
#include <algorithm>
#include <cassert>
#include <limits>
#include <memory>
#include <ranges>

namespace MatrixNS {

  bool in_bounds(const Matrix& mat, int row, int col);

  /********** Matrix ********
   *
   */

  Matrix::Matrix(int width, int height) : width(width), height(height), 
    data(width * height, 0) { }

  int& Matrix::at(int row, int column) {
    assert(in_bounds(*this, row, column));

    return data[row * get_width() + column];
  }

  const int& Matrix::at(int row, int column) const {
    assert(in_bounds(*this, row, column));
    
    return data[row * get_width() + column];
  }

  int Matrix::row_index(const int& el) const {
    return (&el - &data[0]) / get_width();
  }

  int Matrix::col_index(const int& el) const {
    return (&el - &data[0]) % get_width();
  }

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

  Matrix::RowIterator Matrix::RowIterator::operator+(const Matrix::RowIterator::difference_type n) {
    auto tmp(*this);
    tmp.row += n;
    return tmp;
  }

  Matrix::RowIterator Matrix::RowIterator::operator-(const Matrix::RowIterator::difference_type n) {
    auto tmp(*this);
    tmp.row -= n;
    return tmp;
  }

  Matrix::RowIterator::value_type Matrix::RowIterator::operator*() const {
    return {mat, row, col};
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

  Matrix::row_iterator Matrix::row_begin() {
    return {*this, 0};
  }

  Matrix::row_iterator Matrix::row_end() { 
    return {*this, get_height()};
  }

  Matrix::const_row_iterator Matrix::row_cbegin() const {
    return {*this, 0};
  }

  Matrix::const_row_iterator Matrix::row_cend() const { 
    return {*this, get_height()};
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

  void fill(Matrix& mat, int value) {
    std::ranges::fill(mat, value);
  }

  void print(const Matrix& mat, std::ostream& os) {
    os << mat.get_width() << " " <<  mat.get_height() << std::endl;

    for (auto row = mat.row_cbegin(); row != mat.row_cend(); ++row) {
      for (const auto &el : *row) {
        os << el << ' ';
      }

      os << '\n';
    }
  }

  int max(const Matrix& mat) {
    return *std::max_element(mat.cbegin(), mat.cend());
  }

  int column_of_min_value_in_row(const Matrix& mat, int row, int column_start,
                                 int column_end) {

    assert(in_bounds(mat, row, column_start));
    assert(in_bounds(mat, row, column_end-1));
    assert(column_start < column_end);

    auto row_it = mat.row_cbegin() + row;
    auto min_el = std::min_element((*row_it).cbegin() + column_start, (*row_it).cbegin() + column_end);
    auto min_el_idx = std::distance((*row_it).cbegin(), min_el);

    return min_el_idx;
  }

  int min_value_in_row(const Matrix& mat, int row, int column_start, 
                       int column_end) {

    assert(in_bounds(mat, row, column_start));
    assert(in_bounds(mat, row, column_end-1));
    assert(column_start < column_end);
      
    auto min_col = column_of_min_value_in_row(mat, row, column_start, column_end);

    return mat.at(row, min_col);
  }

  bool in_bounds(const Matrix& mat, int row, int col) {
    if (row < 0 || row >= mat.get_height())
      return false;

    if (col < 0 || col >= mat.get_width())
      return false;

    return true;
  }
}

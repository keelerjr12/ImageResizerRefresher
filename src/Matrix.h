#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

namespace MatrixNS {

  const int MAX_MATRIX_WIDTH = 500;
  const int MAX_MATRIX_HEIGHT = 500;

  // Representation of a 2D matrix of integers
  // Matrix objects may be copied.
  class Matrix{

   public:
       
    // EFFECTS:  Initializes this as a Matrix with the given width and height.
    Matrix(int width, int height);

    // EFFECTS:  this as a Matrix with the given width and height.
    Matrix(const Matrix& rhs);
    
    // EFFECTS:  Returns the width of the Matrix.
    int get_width() const { return width; }
    
    // EFFECTS:  Returns the height of the Matrix.
    int get_height() const { return height; }

    // REQUIRES: 0 <= row && row < mat->get_height()
    //           0 <= column && column < mat->get_width()
    // MODIFIES: (The returned reference may be used to modify an
    //            element in the Matrix.)
    // EFFECTS:  Returns a reference to the element in the Matrix
    //           at the given row and column.
    int& at(int row, int column);
    const int& at(int row, int column) const;

    // EFFECTS:  Returns the row of the element pointed to by ptr.
    int row_index(const int& el) const;

    // EFFECTS:  Returns the column of the element pointed to by ptr.
    int col_index(const int& el) const;
    
    // MODIFIES: Data vector
    // EFFECTS:  Sets each element of the Matrix to the given value.
    // void fill(int value);
    
    // MODIFIES: Data vector
    // EFFECTS:  Sets each element on the border of the Matrix to
    //           the given value. These are all elements in the first/last
    //           row or the first/last column.
    void fill_border(int value);

    using iterator = std::vector<int>::iterator;
    using const_iterator = std::vector<int>::const_iterator;

    iterator begin() { return data.begin(); } 
    iterator end() { return data.end(); } 
    const_iterator cbegin() const { return data.cbegin(); } 
    const_iterator cend() const { return data.cend(); } 
    
    class RowVecIterator {

     public:

      using value_type = int; 
      using difference_type = std::ptrdiff_t; 
      using reference = const int&; 
      using pointer = int*;
      using iterator_category = std::forward_iterator_tag;
       
      RowVecIterator(const Matrix& mat, int row, int col);

      RowVecIterator& operator+=(difference_type n);

      RowVecIterator& operator++();
      RowVecIterator operator++(int);

      reference operator*();

      RowVecIterator begin() { return RowVecIterator(*mat, row, 0); }
      RowVecIterator end() { return RowVecIterator(*mat, row, mat->get_width()); }
      RowVecIterator cbegin() const { return RowVecIterator(*mat, row, 0); }
      RowVecIterator cend() const { return RowVecIterator(*mat, row, mat->get_width()); }

      friend bool operator==(const RowVecIterator& lhs, const RowVecIterator& rhs);    
      friend bool operator!=(const RowVecIterator& lhs, const RowVecIterator& rhs);    

      friend RowVecIterator operator+(const RowVecIterator& x, difference_type n);

     private:
      
      const Matrix* mat;
      int row;
      int col;
    };

    class RowIterator {

     public:
       
      using value_type = RowVecIterator;
      using difference_type = std::ptrdiff_t; 
      using reference = RowVecIterator&;
      using pointer = RowVecIterator*;
      using iterator_category = std::input_iterator_tag;

      RowIterator(const Matrix& mat, int row);

      RowIterator& operator++();
      RowIterator operator++(int);

      RowIterator operator+(const difference_type n);
      RowIterator operator-(const difference_type n);

      value_type operator*() const;

      friend bool operator==(const RowIterator& lhs, const RowIterator& rhs);    
      friend bool operator!=(const RowIterator& lhs, const RowIterator& rhs);    

     private:

      const Matrix& mat;
      int row;
      int col;
    };

    using row_iterator = RowIterator;
    using const_row_iterator =  RowIterator;

    row_iterator row_begin();
    row_iterator row_end();
    const_row_iterator row_cbegin() const;
    const_row_iterator row_cend() const;

    friend bool operator==(const Matrix& lhs, const Matrix& rhs);    
    friend bool operator!=(const Matrix& lhs, const Matrix& rhs);    

   private:
    
    int width;
    int height;

    std::vector<int> data;
  };

  // MODIFIES: Matrix mat
  // EFFECTS:  Sets each element of the Matrix to the given value.
  void fill(Matrix& mat, int value);

  // MODIFIES: os
  // EFFECTS:  First, prints the width and height for the Matrix to os:
  //             WIDTH [space] HEIGHT [newline]
  //           Then prints the rows of the Matrix to os with one row per line.
  //           Each element is followed by a space and each row is followed
  //           by a newline. This means there will be an "extra" space at
  //           the end of each line.
  void print(const Matrix& mat, std::ostream& os);

  // EFFECTS:  Returns the value of the maximum element in the Matrix
  int max(const Matrix& mat);

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
  int column_of_min_value_in_row(const Matrix& mat, int row,
                                 int column_start, int column_end);

  // REQUIRES: mat points to a valid Matrix
  //           0 <= row && row < mat->get_height()
  //           0 <= column_start && column_end <= mat->get_width()
  //           column_start < column_end
  // EFFECTS:  Returns the minimal value in a particular region. The region
  //           is defined as elements in the given row and between
  //           column_start (inclusive) and column_end (exclusive).
  int min_value_in_row(const Matrix& mat, int row, int column_start, 
                       int column_end);

}

#endif // MATRIX_H

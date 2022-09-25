#include "Matrix.h"

int main() {
    auto  width = 6;
    auto height = 8;
    auto value = 2;

    Matrix *mat = new Matrix;
    Matrix_init(mat, width, height);

    Matrix *correct_mat = new Matrix;
    Matrix_init(correct_mat, width, height);

    Matrix_fill_border(mat, value);

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
    
    Matrix_print(mat, std::cout);
    Matrix_print(correct_mat, std::cout);
    
    delete correct_mat;
    delete mat;

    return 0;
}

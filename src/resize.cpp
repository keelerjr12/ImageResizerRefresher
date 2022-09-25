#include "Matrix.h"

int main() {
    Matrix *mat = new Matrix;

    Matrix_init(mat, 6, 8);
    Matrix_fill(mat, 1);

    Matrix_print(mat, std::cout);

    delete mat;

    return 0;
}

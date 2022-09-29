#include "Image.h"
#include "Matrix.h"
#include <fstream>

void buf_over(int* arr, int size) {
    for (auto i = 0; i <= size * size; ++i)
        arr[i] = 20;
}

int main() {
    //std::ifstream fs ("data/dog.ppm");
    //auto img = image_from_stream(fs);
    int size = 1400;
    std::cout << &size << std::endl;
    
    int arr[1400 * 1400] = {0};
    arr[1400*1400-1] = 1;
    buf_over(arr, size);
    
    std::cout << (arr) << std::endl;
    std::cout << *(arr+size*size-1) << std::endl;
    
    return 0;
}

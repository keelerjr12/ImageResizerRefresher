#include "Image.h"
#include "Matrix.h"
#include <fstream>

int main() {
    std::ifstream fs ("data/dog.ppm");

    auto img = new Image;
    Image_init(img, fs);

    return 0;
}

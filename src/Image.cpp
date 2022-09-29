// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Image.h"
#include <cassert>
#include <memory>
#include "Matrix.h"

// REQUIRES: 0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: img
// EFFECTS:  Initializes the Image with the given width and height.
Image::Image(int width, int height) 
  : width(width), height(height),
    red_channel(std::make_unique<Matrix>(width, height)),
    green_channel(std::make_unique<Matrix>(width, height)),
    blue_channel(std::make_unique<Matrix>(width, height)) {

  assert(0 < width && width <= MAX_MATRIX_WIDTH);
  assert(0 < height && height <= MAX_MATRIX_HEIGHT);
}

Image::Image(const Image& rhs) {
    std::cout << "Copy ctor" << std::endl;
}

Image& Image::operator=(const Image& rhs) {
    std::cout << "Copy assignment ctor" << std::endl;

    return *this;
}

// REQUIRES: is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: 
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
// NOTE:     Do NOT use new or delete here.
Image image_from_stream(std::istream& is) {
    std::string format;
    is >> format;

    int width;
    is >> width;

    int height;
    is >> height;

    int max_rgb;
    is >> max_rgb;

    auto img = Image(width, height);
    
    auto pixel = 0;
    int r, g, b;

    while (is >> r >> g >> b) {
        *Matrix_at(*img.red_channel, pixel / width, pixel % width) = r;
        *Matrix_at(*img.green_channel, pixel / width, pixel % width) = g;
        *Matrix_at(*img.blue_channel, pixel / width, pixel % width) = b;

        ++pixel;
    }

    return img;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
    os << "P3" << std::endl;
    os << Image_width(img) << " " << Image_height(img) << std::endl;
    os << "255" << std::endl;

    for (auto row = 0; row < Image_height(img); ++row) {
        for (auto col = 0; col < Image_width(img); ++col) {
            os << *Matrix_at(*img->red_channel, row, col) << " ";
            os << *Matrix_at(*img->green_channel, row, col) << " ";
            os << *Matrix_at(*img->blue_channel, row, col) << " ";
        }

        os << std::endl;
    }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
    return img->width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
    return img->height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
    assert(img);
    assert(0 <= row && row < Image_height(img));
    assert(0 <= column && column < Image_width(img));

    Pixel px;
    px.r = *Matrix_at(*img->red_channel, row, column);
    px.g = *Matrix_at(*img->green_channel, row, column);
    px.b = *Matrix_at(*img->blue_channel, row, column);

    return px;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
    assert(img);
    assert(0 <= row && row < Image_height(img));
    assert(0 <= column && column < Image_width(img));

    *Matrix_at(*img->red_channel, row, column) = color.r;
    *Matrix_at(*img->green_channel, row, column) = color.g;
    *Matrix_at(*img->blue_channel, row, column) = color.b;
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
    assert(img);

    Matrix_fill(*img->red_channel, color.r);
    Matrix_fill(*img->green_channel, color.g);
    Matrix_fill(*img->blue_channel, color.b);
}

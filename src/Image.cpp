// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Image.h"
#include <cassert>
#include <memory>
#include "Matrix.h"

// REQUIRES: 0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: this
// EFFECTS:  Initializes the Image with the given width and height.
Image::Image(int width, int height) 
  : width(width), height(height), red_channel(width, height),
    green_channel(width, height), blue_channel(width, height) {

  assert(0 < width && width <= MAX_MATRIX_WIDTH);
  assert(0 < height && height <= MAX_MATRIX_HEIGHT);
}

// REQUIRES: 0 <= row && row < img->get_height()
//           0 <= column && column < img->get_width()
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image::get_pixel(int row, int column) const {
  assert(0 <= row && row < get_height());
  assert(0 <= column && column < get_width());

  Pixel px;
  px.r = red_channel.at(row, column);
  px.g = green_channel.at(row, column);
  px.b = blue_channel.at(row, column);

  return px;
}


// REQUIRES: 0 <= row && row < img->get_height()
//           0 <= column && column < img->get_width()
// MODIFIES: this
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image::set_pixel(int row, int column, const Pixel& color) {
  assert(0 <= row && row < get_height());
  assert(0 <= column && column < get_width());

  red_channel.at(row, column) = color.r;
  green_channel.at(row, column) = color.g;
  blue_channel.at(row, column) = color.b;
}


// REQUIRES: img points to a valid Image
// MODIFIES: this
// EFFECTS:  Sets each pixel in the image to the given color.
void Image::fill(const Pixel& color) {
  Matrix_fill(red_channel, color.r);
  Matrix_fill(green_channel, color.g);
  Matrix_fill(blue_channel, color.b);
}


// REQUIRES: is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: 
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
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
  
  auto px_idx = 0;
  int r, g, b;

  while (is >> r >> g >> b) {
    auto px = Pixel {r, g, b};
    img.set_pixel(px_idx / width, px_idx % width, px);
    ++px_idx;
  }

  return img;
}

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
void Image_print(const Image& img, std::ostream& os) {
  os << "P3" << std::endl;
  os << img.get_width() << " " << img.get_height() << std::endl;
  os << "255" << std::endl;

  for (auto row = 0; row < img.get_height(); ++row) {
    for (auto col = 0; col < img.get_width(); ++col) {
      auto px = img.get_pixel(row, col);
      os << px.r << " ";
      os << px.g << " ";
      os << px.b << " ";
    }

    os << std::endl;
  }
}

#ifndef IMAGE_H
#define IMAGE_H

/* Image.h
 * Project UID af1f95f547e44c8ea88730dfb185559d
 * Originally written by James Juett at the University of Michigan
 * for project 3 in EECS 280, Winter 2016.
 */

#include <iostream>
#include "Matrix.h"

// Representation of an RGB Pixel used for
// parameter passing and returns by the
// Image module. This is a POD type.
struct Pixel {
  int r;
  int g;
  int b;
};

const int MAX_INTENSITY = 255;

// Representation of 2D RGB image.
// Image objects may be copied.
class Image {
 public:

  Image(int width, int height);
  
  // EFFECTS:  Returns the width of the Image.
  int get_width() const { return width; }
   
  // EFFECTS:  Returns the height of the Image.
  int get_height() const { return height; }

  // REQUIRES: 0 <= row && row < img->get_height()
  //           0 <= column && column < img->get_width()
  // EFFECTS:  Returns the pixel in the Image at the given row and column.
  Pixel get_pixel(int row, int column) const;

  // REQUIRES: 0 <= row && row < img->get_height()
  //           0 <= column && column < img->get_width()
  // MODIFIES: this
  // EFFECTS:  Sets the pixel in the Image at the given row and column
  //           to the given color.
  void set_pixel(int row, int column, const Pixel& color); 
      
  // MODIFIES: this
  // EFFECTS:  Sets each pixel in the image to the given color.
  void fill(const Pixel& color);
  
 private:

  int width;
  int height;

  Matrix red_channel;
  Matrix green_channel;
  Matrix blue_channel;
};


// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: 
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
Image image_from_stream(std::istream& is);


// REQUIRES: img points to a valid Image
// MODIFIES: os
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
void Image_print(const Image& img, std::ostream& os);


#endif // IMAGE_H

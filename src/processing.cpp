// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include <limits>
#include "processing.h"

using namespace std;
using namespace ImageNS;
using namespace MatrixNS;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = img->get_width();
  int height = img->get_height();

  // auxiliary image to temporarily store rotated image
  auto aux = Image(width, height);

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      aux.set_pixel(width - 1 - c, r, img->get_pixel(r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = img->get_width();
  int height = img->get_height();

  // auxiliary image to temporarily store rotated image
  auto aux = Image(width, height);

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      aux.set_pixel(c, height - 1 - r, img->get_pixel(r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
Matrix compute_energy_matrix(const Image* img) {
  assert(img);

  auto energy = Matrix(img->get_width(), img->get_height());
    
  for (auto r = 1; r < energy.get_height() - 1; ++r) {
    for (auto c = 1; c < energy.get_width() - 1; ++c) {
      const auto pixel_n = img->get_pixel(r-1, c); 
      const auto pixel_s = img->get_pixel(r+1, c); 
      const auto pixel_w = img->get_pixel(r, c-1); 
      const auto pixel_e = img->get_pixel(r, c+1); 

      const auto e = squared_difference(pixel_n, pixel_s) + squared_difference(pixel_w, pixel_e);
      energy.at(r, c) = e;
    }
  }

  const auto max =  MatrixNS::max(energy);
  energy.fill_border(max);

  return energy;
}


// REQUIRES: energy points to a valid Matrix.
// MODIFIES: 
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
Matrix compute_vertical_cost_matrix(const Matrix* energy) {
  assert(energy);

  auto cost = Matrix(energy->get_width(), energy->get_height());

  // compute 1st row
  for (auto c = 0; c < energy->get_width(); ++c) {
      cost.at(0, c) = energy->at(0, c);
  }

  // compute subsequent rows
  for (auto r = 1; r < energy->get_height(); ++r) {
    // compute 0th col
    auto min_cost = min_value_in_row(cost, r-1, 0, 2);
    cost.at(r, 0) = energy->at(r, 0) + min_cost;

    // compute middle cols
    for (auto c = 1; c < energy->get_width()-1; ++c) {
      min_cost = min_value_in_row(cost, r-1, c-1, c+2);
      cost.at(r, c) = energy->at(r, c) + min_cost;
    }
    
    // compute last col
    min_cost = min_value_in_row(cost, r-1, energy->get_width()-2, energy->get_width());
    cost.at(r, energy->get_width()-1) = energy->at(r, energy->get_width()-1) + min_cost;
  }

  return cost;
}


// REQUIRES: cost points to a valid Matrix
//           seam points to an array
//           the size of seam is >= Matrix_height(cost)
// MODIFIES: seam[0]...seam[Matrix_height(cost)-1]
// EFFECTS:  seam serves as an "output parameter".
//           The vertical seam with the minimal cost according to the given
//           cost matrix is found and the seam array is filled with the column
//           numbers for each pixel along the seam, with the pixel for each
//           row r placed at seam[r]. While determining the seam, if any pixels
//           tie for lowest cost, the leftmost one (i.e. with the lowest
//           column number) is used.
//           See the project spec for details on computing the minimal seam.
// NOTE:     You should compute the seam in reverse order, starting
//           with the bottom of the image and proceeding to the top,
//           as described in the project spec.
void find_minimal_vertical_seam(const Matrix* cost, int seam[]) {
  assert(false); // TODO Replace with your implementation!
}


// REQUIRES: img points to a valid Image with width >= 2
//           seam points to an array
//           the size of seam is == img->get_height()
//           each element x in seam satisfies 0 <= x < img->get_width()
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Use the new operator here to create the smaller Image,
//           and then use delete when you are done with it.
void remove_vertical_seam(Image *img, const int seam[]) {
  assert(false); // TODO Replace with your implementation!
}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= img->get_width()
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use the new operator here to create Matrix objects, and
//           then use delete when you are done with them.
void seam_carve_width(Image *img, int newWidth) {
  assert(false); // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= img->get_height()
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
  assert(false); // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= img->get_width()
//           0 < newHeight && newHeight <= img->get_height()
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {
  assert(false); // TODO Replace with your implementation!
}

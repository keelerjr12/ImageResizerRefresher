#ifndef PROCESSING_H
#define PROCESSING_H

#include "Matrix.h"
#include "Image.h"

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(ImageNS::Image* img);

// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(ImageNS::Image* img);

// REQUIRES: img points to a valid Image.
// MODIFIES: 
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
MatrixNS::Matrix compute_energy_matrix(const ImageNS::Image* img);

// REQUIRES: energy points to a valid Matrix.
// MODIFIES: 
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
MatrixNS::Matrix compute_vertical_cost_matrix(const MatrixNS::Matrix* energy);

// REQUIRES: cost points to a valid Matrix
//           seam points to an array
//           the size of seam is >= Matrix_height(cost)
// MODIFIES: seam[0]...seam[Matrix_height(cost)-1]
// EFFECTS:  seam serves as an "output parameter".
//           The vertical seam with the minimal cost according to the given
//           cost matrix is found and the seam array is filled with the column
//           numbers for each pixel along the seam, starting with the lowest
//           numbered row (top of image) and progressing to the highest
//           (bottom of image). While determining the seam, if any pixels
//           tie for lowest cost, the leftmost one (i.e. with the lowest
//           column number) is used.
//           See the project spec for details on computing the minimal seam.
void find_minimal_vertical_seam(const MatrixNS::Matrix* cost, int seam[]);

// REQUIRES: img points to a valid Image
//           Image_width(img) >= 2
//           seam points to an array
//           the size of seam is == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
void remove_vertical_seam(ImageNS::Image *img, const int seam[]);

// REQUIRES: img points to a valid Image
//           0 < newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
void seam_carve_width(ImageNS::Image *img, int newWidth);

// REQUIRES: img points to a valid Image
//           0 < newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(ImageNS::Image *img, int newHeight);

// REQUIRES: img points to a valid Image
//           0 < newWidth <= Image_width(img)
//           0 < newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(ImageNS::Image *img, int newWidth, int newHeight);


#endif // PROCESSING_H

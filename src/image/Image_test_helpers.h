#ifndef IMAGE_TEST_HELPERS_H
#define IMAGE_TEST_HELPERS_H

/* Image_test_helpers.h
 * Project UID af1f95f547e44c8ea88730dfb185559d
 * Originally written by James Juett at the University of Michigan
 * for project 3 in EECS 280, Winter 2016.
 */

#include "Image.h"

// EFFECTS: Returns true if p1 and p2 are equal. Returns false otherwise.
bool Pixel_equal(ImageNS::Pixel p1, ImageNS::Pixel p2);

// REQUIRES: img1 points to a valid Image
//           img2 points to a valid Image
// EFFECTS:  Returns true if img1 and img2 are the same size and
//           contain exactly the same pixels. Returns false otherwise.
bool Image_equal(const ImageNS::Image* img1, const ImageNS::Image* img2);

#endif // IMAGE_TEST_HELPERS_H

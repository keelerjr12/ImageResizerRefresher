// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Image.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <sstream>
#include <string>

using std::string;
using namespace ImageNS;

// This is the public Image test for which the autograder gives feedback.
// It only tests VERY FEW of the expected behaviors of the Image module.
// It will only really tell you if your code compiles and you remembered to
// write the functions. It is not to be trusted. It tells the truth, but not
// the whole truth. It might put you in a blender. You get the point.
// You must write your own comprehensive unit tests in Image_tests.cpp!


TEST(test_image_basic) {
  Pixel red = {255, 0, 0};
  Pixel green = {0, 255, 0};
  auto width = 3;
  auto height = 4;

  auto img = Image(width, height);

  ASSERT_EQUAL(img.get_width(), 3);
  ASSERT_EQUAL(img.get_height(), 4);

  img.fill(red);
  ASSERT_TRUE(Pixel_equal(img.get_pixel(2, 2), red));

  img.set_pixel(0, 0, green);
  ASSERT_TRUE(Pixel_equal(img.get_pixel(0, 0), green));
}

TEST(test_image_from_and_to_stream) {
  // A very poorly behaved input PPM.
  string input = "P3 2 2\t255 255 0 0\n0\n255 0 \n0 0 255 255 255 255 \n";
  std::istringstream ss_input(input);
  auto img = from_stream(ss_input);

  // Should be well behaved when you print it though!
  string output_correct = "P3\n2 2\n255\n255 0 0 0 255 0 \n0 0 255 255 255 255 \n";
  std::ostringstream ss_output;
  print(img, ss_output);
  string actual = ss_output.str();

  ASSERT_EQUAL(actual, output_correct);
}

TEST_MAIN()

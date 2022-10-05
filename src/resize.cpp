#include <iostream>
#include "Image.h"

using namespace ImageNS;

int main() {
  auto img = Image(10, 20);
  auto img2 = img;

  return 0;
}

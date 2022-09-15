#include "BMP.h"
#include <cmath>
#include <iostream>

int main() {

  BMP bmpNew(769, 769, false);
  bmpNew.fill_region(0, 0, 200, 200, 0, 0, 0, 0);
  for (int i = 0; i < bmpNew.bmp_info_header.width; i++) {
    int y = ((sqrt((768 + i) * (768 - i))) / 2) + 384;
    int yBottom = -((sqrt((768 + i) * (768 - i))) / 2) + 384;
    bmpNew.set_pixel(i, y, 255, 255, 255, 0);
    bmpNew.set_pixel(i, yBottom, 255, 255, 255, 0);
  }
  bmpNew.write("output.bmp");
}

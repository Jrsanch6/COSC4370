#include "BMP.h"
#include <cmath>
#include <iostream>

int main() {

  BMP bmpNew(800, 800, false);
  bmpNew.fill_region(0, 0, 200, 200, 0, 0, 0, 0);
  for (float i = 0; i < bmpNew.bmp_info_header.width; i = i + 0.001){
    float y = ((sqrt((768 + i) * (768 - i))) / 2) + 384;
    float yBottom = -((sqrt((768 + i) * (768 - i))) / 2) + 384;
    bmpNew.set_pixel(i, y, 255, 255, 255,0);
    bmpNew.set_pixel(i, yBottom, 255, 255, 255, 0);
  }
  bmpNew.write("output.bmp");
}

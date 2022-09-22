#include "BMP.h"
#include <cmath>
#include <iostream>

int main() {
  BMP bmpNew(800, 800, false);

  bmpNew.fill_region(0, 0, 200, 200, 0, 0, 0, 0);
  // For loop to draw the pixels for the ellipse every 0.001 x coordinate
  for (float i = 0; i < 768; i = i + 0.001) {
    // float y and yBottom variables to have the upper side of the ellipse and
    // the bottom side of it
    float y = ((sqrt((768 + i) * (768 - i))) / 2) + 384;
    float yBottom = -((sqrt((768 + i) * (768 - i))) / 2) + 384;

    // Drawing the bottom and top part of the ellipse
    bmpNew.set_pixel(i, y, 255, 255, 255, 0);
    bmpNew.set_pixel(i, yBottom, 255, 255, 255, 0);
  }
  // Outputting it all to output.bmp
  bmpNew.write("output.bmp");
}

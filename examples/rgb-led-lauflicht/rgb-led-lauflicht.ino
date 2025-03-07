#include <AALeC-V3.h>

const uint8_t numLeds = 5;
uint8_t nr = 0;
uint8_t colorIndex = 0;
const RgbColor colors[] = {c_red, c_green, c_blue, c_yellow, c_white, c_cyan, c_purple};

void setup() {
  aalec.init(numLeds);
}

void loop() {
  if (aalec.get_button()) {
    colorIndex = (colorIndex + 1) % (sizeof(colors) / sizeof(colors[0])); 
  }

  aalec.set_rgb_strip(nr, c_off);
  nr = (nr + 1) % numLeds;
  aalec.set_rgb_strip(nr, colors[colorIndex]);
  delay(aalec.get_analog());
}

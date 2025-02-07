#include <AALeC-V3.h>

void setup() {
  aalec.init();
}

void loop() {
  static uint32_t n = 0;
  for(int i = 0; i<5; i++) {
    aalec.set_rgb_strip(i, n);
  }
  n++;
  delay(10);
}

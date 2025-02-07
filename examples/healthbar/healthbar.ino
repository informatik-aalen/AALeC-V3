#include <AALeC-V3.h>

uint8_t colors[][3] = {
    {255, 0, 0}, {254, 46, 0}, {252, 69, 0}, {249, 86, 0}, {245, 102, 0},
    {239, 117, 0}, {232, 130, 0}, {226, 143, 0}, {218, 154, 0}, {210, 165, 0},
    {202, 175, 0}, {193, 184, 0}, {183, 194, 0}, {172, 203, 0}, {160, 212, 0},
    {146, 221, 0}, {128, 230, 0}, {104, 239, 0}, {74, 247, 0}, {0, 255, 0}
};

int maxHealth = 100;
int health;

void setup() {
  // put your setup code here, to run once:
  aalec.init();
  aalec.set_rgb_strip(0, 255, 0, 255);
}

void loop() {
  // put your main code here, to run repeatedly:
  health = maxHealth - aalec.get_rotate();
  if(health > maxHealth) {
    health = maxHealth;
  }
  if(health < 0) {
    health = 0;
  }
  aalec.print_line(3, "Health: " + (String)health);

  for(int i = 0; i < 5; i++) {
    if(health >= (i + 1) * 20) {
      aalec.set_rgb_strip(i, c_green);
    } else if(health > i * 20) {
      int index = health % 20;
      aalec.set_rgb_strip(i, colors[index][0], colors[index][1], colors[index][2]);
    } else {
      aalec.set_rgb_strip(i, c_red);
    }
  }

}

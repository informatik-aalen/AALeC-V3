#include <AALeC-V3.h>
void setup() {
  aalec.init();
  aalec.print_line(5, "aalec: Hochschule Aalen");
}

void loop() {
  const static RgbColor ampel[4][5] = { // Achtung LED 0 ist unten und LED 2 ist oben!
    {c_off, c_off, c_red, c_off, c_off}, {c_off, c_yellow, c_red, c_off, c_off}, {c_green, c_off, c_off, c_off, c_off}, {c_off, c_yellow, c_off, c_off, c_off}
  };
  static uint32_t t = millis(), ampelnr, b, t_ampel = 2000;

  if (millis() - t >= t_ampel) {
    aalec.set_rgb_strip(ampel[ampelnr]);
    Serial.println(ampelnr);
    t += t_ampel, ampelnr = (ampelnr + 1) % 4;
  }
  // OLED-Ausgabe über aalec-Library: Einfach
  aalec.print_line(1, aalec.get_environment_sensor() + " erkannt");
  aalec.print_line(2, (String) aalec.get_button() + " " + (String) aalec.get_rotate());
  // Direktzugriff auf display: Nicht einfach
  aalec.display.setColor(BLACK);
  aalec.display.fillRect(0, 30, 128, 12);
  aalec.display.drawProgressBar(0, 30, 128, 12, (int) (aalec.get_analog() / 10.24));
  aalec.display.display();
  if (b != aalec.get_button())
    b = !b, aalec.play((b) ? t_a_1 : t_off);
}

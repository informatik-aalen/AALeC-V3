// To run this program correctly, two AALeCs must be connected to each other via the serial interface.
// The script must run on both AALeCs. The buzzer must also be deactivated.

#include <AALeC-V3.h>
void setup() {
  aalec.init();
  aalec.serial_swap();
  delay(1000);
}

void loop() {
  if (Serial.available()) {
    String received = Serial.readStringUntil('\n');
    aalec.print_line(1, "Received: " + received);

    Serial.println((String) aalec.get_rotate());
  }

  delay(10);
}

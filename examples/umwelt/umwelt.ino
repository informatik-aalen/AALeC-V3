#include <AALeC-V3.h>
void setup() {
  aalec.init();
  aalec.print_line(1, aalec.get_environment_sensor() + " erkannt");
}

void loop() {
  aalec.print_line(2, "Temperature: " + (String) aalec.get_temp() + " °C");
  aalec.print_line(3, "Humidity: " + (String) aalec.get_humidity() + " %");
  aalec.print_line(4, "Pressure: " + (String) aalec.get_pressure() + " hPa");
  aalec.print_line(5, "Gas Resist.: " + (String) aalec.get_gas_resistance() + " kOhm");
  delay(100);
}

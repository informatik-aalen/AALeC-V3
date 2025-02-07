#include "ESP8266WiFi.h"
#include <AALeC-V3.h>


void setup()
{
  aalec.init();
}

void loop() {
  static uint32_t delta_t = 10000, t = millis() - delta_t, nr;
  if (millis() - t >= delta_t) {
    int n;
      uint8_t encryptionType;
  int32_t RSSI;
  uint8_t* BSSID;
  int32_t channel;
  bool isHidden;
  String ssid;

  aalec.set_rgb_strip(0, c_red);
    t += delta_t;
    n = WiFi.scanNetworks();
  aalec.set_rgb_strip(0, c_off);
    aalec.clear_display();
    Serial.println("##############");
    for (int i = 0; i < n; i++)
  {
 WiFi.getNetworkInfo(i, ssid, encryptionType, RSSI, BSSID, channel, isHidden);
    String txt =  (String) ssid + ": " + (String) RSSI;
  Serial.println(txt);
  aalec.print_line(i+1, txt);
  }
  }

}

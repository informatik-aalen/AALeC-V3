# AALeC V3 - AAlener Lern-Computer

## Beschreibung

AALeC ist der Aalener Lerncomputer. Er basiert auf einem ESP8266, welcher als
Wemos-D1-Mini-Modul eingesetzt wird.

Sensoren:
* BME280- oder BME680-Umweltsensor für Temperatur, Luftfeuchte, etc.
* Dreh- /  Drückgeber
* Analoges Potentiometer

Aktoren / Ausgabeelemente:
* Fünf Fullcolor-Leuchtdioden WS2812B
* OLED-Display
* Lautsprecher

Externe Anschlüsse:
* I2C
* WS2812-Ausgang
* Serielle Schnittstelle via SerialSwap
* Analogeingang (3,5mm-Klinke)
* Wii-Nunchuck

Die Programmierung kann in allen Sprachen erfolgen, die für den ESP8266
verfügbar sind. Für Arduino-Programmierung in C / C++ steht diese Bibliothek zur
Verfügung, die die Programmierung stark vereinfacht.

## GPIO-Belegung

 0  Drehgeber Taster \
 1  TX \
 2  WS2812-Kette \
 3  RX \
 4  SDA \
 5  SCL \
12  Drehgeber Spur 0 \
13  SerialSwap RX
14  Drehgeber Spur 1 \
15  Lautsprecher / SerialSwap TX \
16  Reset

## Installation

Laden Sie unter [https://github.com/informatik-aalen/AALeC-V3/releases](https://github.com/informatik-aalen/AALeC-V3/releases)
die .ZIP Datei der aktuellen Version der Bibliothek herunter. Benutzen Sie den
Menüpunkt **.ZIP Bibliothek hinzufügen...** unter dem Menü **Sketch** -> 
**Bibliothek einbinden** in der Arduino IDE um die Bibliothek einzubinden.

## Abhängigkeiten

Diese Bibliothek hängt von den folgenden Bibliotheken ab:
* Adafruit_Neopixel
* ESP8266 and ESP32 Oled Driver for SSD1306 display
* WiiChuck
* Adafruit Sensor
* Adafruit BME280
* Adafruit BME680

Installieren Sie diese Bibliotheken bitte über den Bibliotheksverwalter in der Arduino IDE.
Zur Ausführung werden beide BME-Bibliotheken benötigt, da die AALeC-Bibliothek automatisch erkennt, welcher Sensor an den AALeC angeschlossen ist.

## Autoren

* **Winfried Bantel** - *Idee und Codierung*
* **Peter Kolb** - *Schaltplan, Layout, CAD, Mechanik*
* **Sebastian Stigler** - *Codierung*
* **Andre Stegmaier** - *Codierung*

## Lizenz

Das Projekt wird unter der MIT-Lizenz publiziert.

## Nachbau und Vertrieb

Nachbau ist explizit erwünscht. Fertigung und Vertrieb der Platine sind unter
Angabe der Hochschule Aalen erlaubt.

Informationen zur Hardware finden Sie unter [https://github.com/informatik-aalen/AALeC-Hardware](https://github.com/informatik-aalen/AALeC-Hardware).

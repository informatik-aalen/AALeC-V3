#ifndef __AALEC_V3_H
#define __AALEC_V3_H

#include <Adafruit_NeoPixel.h>
#include "SH1106Wire.h"
#include <WiiChuck.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_BME680.h>

#define PIN_BUTTON           0
#define PIN_TX               1
#define PIN_RGB_STRIP        2
#define PIN_RX               3
#define PIN_SDA              4
#define PIN_SDC              5
#define PIN_ENCODER_TRACK_1 12
#define PIN_ENCODER_TRACK_2 14
#define PIN_BEEPER          15
#define PIN_RESET           16

// I2C addresses for the sensors
#define BME280_ADDR 0x76
#define BMP280_ADDR 0x76
#define BME680_ADDR 0x77

/* Predefined colors for the three rgb LED's */

typedef struct {
    unsigned char r, g, b;
} RgbColor;

const RgbColor c_red = {200, 0, 0},
c_green  = {0, 200, 0},
c_blue = {0, 0, 200},
c_yellow = {100, 100, 0},
c_white = {66, 66, 66},
c_cyan = {0, 100, 100},
c_purple = {100, 0, 100},
c_off = {0, 0, 0};

/* Some predefined frequencies of tones for the beeper */
enum {t_off = 0, t_c_1 = 262, t_d_1 = 294, t_e_1 = 330, t_f_1 = 349,
	t_g_1 = 392, t_a_1 = 440, t_h_1 = 494, t_c_2 = 523, t_a_2 = 880
};

class c_AALeC_V3 {
	public:
	c_AALeC_V3();
	void init(int numLeds = 5);
	const char * id();
	enum NunchuckValuesEnum {
		JoystickX,
		JoystickY,
		ButtonZ,
		ButtonC,
		Roll,
		Pitch,
		AccelX,
		AccelY,
		AccelZ
	};

	using NunchuckValues = NunchuckValuesEnum;
	
	/* Methods for the three rgb LED's */
    void set_rgb_strip(int, unsigned int);
	void set_rgb_strip(int, uint8_t, uint8_t, uint8_t);
    void set_rgb_strip(int, const RgbColor &);
	void set_rgb_strip(const RgbColor *);
	
	/* Methods for the press button on the encoder */
	int get_button();
	int button_changed();
	
	/* Methods for the value of the encoder */
	int get_rotate();
	int rotate_changed();
	void reset_rotate(int n = 0);
	
	/* Methods for the environment sensor */
	String get_environment_sensor();
	float get_temp();
	float get_humidity();
	float get_pressure();
	float get_gas_resistance();

	
	/* Method for the potentiomether */
	uint16_t get_analog();
	
	/* Methods for the display */
	template <class T>    void print_line(unsigned int, const T &);
	void clear_display();

	/* Methods for the Nunchuck */
	void read_Nunchuck_Data();
	uint8_t get_Nunchuck_Data(NunchuckValues value);
	
	/* Methods for the beeper */
	void play(unsigned int freq);
	void play(unsigned int freq, unsigned int dur);
	void serial_swap();
	
	/* Interupt service routine for the encoder */
	friend void AALeC_V3_ISR_DREH();
	
	/* Attribut for the display */
	SH1106Wire display = SH1106Wire(0x3c, SDA, SCL); //GEOMETRY_128_64);   // ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h e.g. https://github.com/esp8266/Arduino/blob/master/variants/nodemcu/pins_arduino.h

	private:
	void bme680_mess();
	int drehgeber_int = 0, drehgeber_int_alt = 0;
	int button_int = 0, button_int_alt = 0;
	int numLeds = 0;

	Accessory nunchuck1;
	uint8_t nunchValues[9];

	// Create sensor objects
	Adafruit_BME280 bme280;
	Adafruit_BMP280 bmp280;
	Adafruit_BME680 bme680;
	// Flags to indicate which sensor is active
	bool isBME280 = false;
	bool isBMP280 = false;
	bool isBME680 = false;
	uint32_t last_bme680 = -1010;


    Adafruit_NeoPixel * strip;
} ;

template <class T> void c_AALeC_V3::print_line(unsigned int line, const T & s) {
	display.setColor(BLACK);
	display.fillRect(0, ((line - 1) % 5) * 12, 128, 12);
	display.setColor(WHITE);
	display.drawString(0, ((line - 1) % 5) * 12 ,  String(s));
	display.display();
}

/* Default instance of the c_AALeC class */
extern c_AALeC_V3  aalec;

#endif



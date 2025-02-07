#include <Arduino.h>
#include <AALeC-V3.h>


void ICACHE_RAM_ATTR AALeC_V3_ISR_DREH() {
	static int16_t val, z, n;
	const static int8_t delta[4][4] = {
		{0, 1, 2, 0},
		{0, 1, 0, 3},
		{0, 0, 2, 3},
		{0, 1, 2, 3}
	},
	lambda[4][4] = {
		{  0,  1, -1,  0},
		{ -1,  0,  0,  1},
		{  1,  0,  0, -1},
		{  0, -1,  1,  0}
	};
	noInterrupts();
	val = (~GPIO_REG_READ(GPIO_IN_ADDRESS) >> PIN_ENCODER_TRACK_1 & 1) | 
      ((~GPIO_REG_READ(GPIO_IN_ADDRESS) >> (PIN_ENCODER_TRACK_2 - 1) & 2));
	n += lambda[z][val], z = delta[z][val];
	if (z == 0) {
		if (n == 4)
			aalec.drehgeber_int--;
		else if (n == -4)
			aalec.drehgeber_int++;
		n = 0;
	}
	interrupts();
}


c_AALeC_V3::c_AALeC_V3() {
}


void c_AALeC_V3::init() {
	
	pinMode(PIN_BEEPER, OUTPUT);
	pinMode(PIN_LED_RESET, OUTPUT);
	pinMode(PIN_BUTTON, INPUT_PULLUP);
	pinMode(PIN_ENCODER_TRACK_1, INPUT_PULLUP);
	pinMode(PIN_ENCODER_TRACK_2, INPUT_PULLUP);
	
	GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 0xFFFF);
	attachInterrupt(PIN_ENCODER_TRACK_1, AALeC_V3_ISR_DREH, CHANGE);
	attachInterrupt(PIN_ENCODER_TRACK_2, AALeC_V3_ISR_DREH, CHANGE);
	
	Serial.begin(115200);
	while (!Serial)
		delay(100);
	Serial.println("AALeC init");
	Serial.flush();
	
	Wire.begin();
	strip = new Adafruit_NeoPixel(100, PIN_RGB_STRIP, NEO_GRB + NEO_KHZ800);
	strip->begin();
	strip->clear();
	for (int i = 0; i < 100; i++)
		set_rgb_strip(i, 0, 0, 0);
	strip->show();
	
	
	display.init();
	display.flipScreenVertically();
	display.setFont(ArialMT_Plain_10);
	display.setTextAlignment(TEXT_ALIGN_LEFT);

	nunchuck1.begin();
  	if(nunchuck1.type == Unknown) {
    	nunchuck1.type = NUNCHUCK;
  	}

	// Try to initialize BME280
    if (bme280.begin(BME280_ADDR)) {
        isBME280 = true;
    } 
    // Try to initialize BME680 if BME280 not found
    else if (bme680.begin(BME680_ADDR)) {
        isBME680 = true;

        // Configure BME680 settings
        bme680.setTemperatureOversampling(BME680_OS_8X);
        bme680.setHumidityOversampling(BME680_OS_2X);
        bme680.setPressureOversampling(BME680_OS_4X);
        bme680.setIIRFilterSize(BME680_FILTER_SIZE_3);
        bme680.setGasHeater(320, 150); // 320°C for 150ms
    } 
}

const char * c_AALeC_V3::id() {
	const static String myId = "AALeC-" + String(ESP.getChipId(), HEX);
	return myId.c_str();
}

void c_AALeC_V3::set_rgb_strip(int led, unsigned int x) {
    uint16_t r = x % 768, g = (x + 256) % 768, b = (x + 512) % 768;
	set_rgb_strip(led,
           (r < 256) ? r : ((r < 512) ? 511 - r : 0),
           (g < 256) ? g : ((g < 512) ? 511 - g : 0),
           (b < 256) ? b : ((b < 512) ? 511 - b : 0)
      );
}



void c_AALeC_V3::set_rgb_strip(int led, uint8_t r, uint8_t g, uint8_t b) {
	strip->setPixelColor(led, strip->Color(r, g, b));
	strip->show();
}


void c_AALeC_V3::set_rgb_strip(int led, const RgbColor & c) {
	set_rgb_strip(led, c.r, c.g, c.b);
}


void c_AALeC_V3::set_rgb_strip(const RgbColor * c) {
	for (int i = 0; i < 5; i++)
		strip->setPixelColor(i, strip->Color(c[i].r, c[i].g, c[i].b));
	strip->show();
}


int c_AALeC_V3::get_button() {
	return  ~GPIO_REG_READ(GPIO_IN_ADDRESS)  & 1;
}


int c_AALeC_V3::get_rotate() {
	return drehgeber_int;
}


int c_AALeC_V3::rotate_changed() {
	int rc = 0;
	if (drehgeber_int !=drehgeber_int_alt)
		rc = 1, drehgeber_int_alt = drehgeber_int;
	return rc;
}


void c_AALeC_V3::reset_rotate() {
	drehgeber_int = 0;
}


String c_AALeC_V3::get_environment_sensor() {
	if(isBME280) {
		return "BME280";
	} else if(isBME680) {
		return "BME680";
	} else {
		return "Kein Sensor";
	}
}

float c_AALeC_V3::get_temp() {
	if(isBME280) {
		return bme280.readTemperature();
	} else if(isBME680) {
		bme680_mess();
		return bme680.temperature;
	} else {
		return 0.0f;
	}
}

float c_AALeC_V3::get_humidity() {
	if(isBME280) {
		return bme280.readHumidity();
	} else if(isBME680) {
		bme680_mess();
		return bme680.humidity;
	} else {
		return 0.0f;
	}
}

float c_AALeC_V3::get_pressure() {
	if(isBME280) {
		return (bme280.readPressure() / 100.0f);
	} else if(isBME680) {
		bme680_mess();
		return (bme680.pressure / 100.0f);
	} else {
		return 0.0f;
	}
}

float c_AALeC_V3::get_gas_resistance() {
	if(isBME680) {
		bme680_mess();
		return (bme680.gas_resistance / 1000.0f);
	} else {
		return 0.0f;
	}
}


uint16_t c_AALeC_V3::get_analog() {
	return analogRead(A0);
}


void c_AALeC_V3::clear_display() {
	display.clear();
}

void c_AALeC_V3::read_Nunchuck_Data() {
	nunchuck1.readData();
	nunchValues[0] = nunchuck1.values[0];
	nunchValues[1] = nunchuck1.values[1];
	nunchValues[2] = nunchuck1.values[10];
	nunchValues[3] = nunchuck1.values[11];
	nunchValues[4] = nunchuck1.values[2];
	nunchValues[5] = nunchuck1.values[3];
}

uint8_t c_AALeC_V3::get_Nunchuck_Data(NunchuckValues value) {
	return nunchValues[value];
}


void c_AALeC_V3::play(unsigned int f) {
	if (f)
	tone(PIN_BEEPER, f);
	else
	noTone(PIN_BEEPER);
}


void c_AALeC_V3::play(unsigned int f, unsigned int dur) {
	tone(PIN_BEEPER, f, dur);
}

void c_AALeC_V3::serial_swap() {
	pinMode(PIN_BEEPER, INPUT);
	Serial.swap();
}

void c_AALeC_V3::bme680_mess() {
	uint32_t t = millis();
	if (t - last_bme680 >= 1000) {
		bme680.performReading();
		last_bme680 = t;
	}
}

c_AALeC_V3 aalec;

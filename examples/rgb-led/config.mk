THIS_DIR := $(realpath $(dir $(realpath $(lastword $(MAKEFILE_LIST)))))
ROOT := $(THIS_DIR)/..
LIBS = $(ESP_LIBS)/SPI \
  $(ESP_LIBS)/Wire \
  $(ESP_LIBS)/ESP8266WiFi\
  $(ESP_LIBS)/ESP8266HTTPClient\
  $(ESP_LIBS)/ESP8266WebServer\
  $(ESP_LIBS)/Hash\
  /Users/wbantel/Documents/Arduino/libraries/
BOARD = d1_mini
UPLOAD_SPEED = 1000000
FLASH_DEF: 4M2M

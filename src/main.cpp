#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <SoilMoistureSensor.h>
#include <DisplayManager.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int AirValue = 790;
const int WaterValue = 390;
const int SensorPin = A0;

SoilMoistureSensor soilMoistureSensor(SensorPin, AirValue, WaterValue);
DisplayManager displayManager(display);

void setup() {
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  int soilMoistureValue = soilMoistureSensor.readSoilMoisture();
  int soilMoisturePercent = soilMoistureSensor.calculatePercentage(soilMoistureValue);
  displayManager.showSoilMoisture(soilMoistureValue, soilMoisturePercent);
}

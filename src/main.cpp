#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <SoilMoistureSensor.h>
#include <DisplayManager.h>
#include <ESP8266WiFi.h>
#include "secrets.h"
#include "InfluxDBManager.h"
#include "WateringManager.h"
#include "UnderThresholdStrategy.h"

#define SCREEN_WIDTH 128      // OLED display width, in pixels
#define SCREEN_HEIGHT 64      // OLED display height, in pixels
#define OLED_RESET -1         // Reset pin # (or -1 if sharing Arduino reset pin)
#define WATERING_RELAY_PIN D3 // Define the pin for the watering relay module

const int AIR_VALUE = 790;
const int WATER_VALUE = 390;
const int SENSORPIN = A0;
const int WATERING_THRESHOLD = 50;
const int WATERING_DURATION_MILLIS = 2000;

SoilMoistureSensor soilMoistureSensor(SENSORPIN, AIR_VALUE, WATER_VALUE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DisplayManager displayManager(display);
InfluxDBManager influxDBManager(SECRET_INFLUXDB_URL, SECRET_INFLUXDB_ORG, SECRET_INFLUXDB_BUCKET, SECRET_INFLUXDB_TOKEN);
UnderThresholdStrategy strategy(WATERING_THRESHOLD, WATERING_DURATION_MILLIS);
WateringManager wateringManager(WATERING_RELAY_PIN, &strategy);

void connectToWiFi()
{
  WiFi.begin(SECRET_WIFI_SSID, SECRET_WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void setup()
{
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  connectToWiFi();

  influxDBManager.init("PlantSaver", SECRET_WIFI_SSID);
}

void loop()
{
  int soilMoistureValue = soilMoistureSensor.readSoilMoisture();
  int soilMoisturePercent = soilMoistureSensor.calculatePercentage(soilMoistureValue);

  displayManager.showSoilMoisture(soilMoistureValue, soilMoisturePercent);

  influxDBManager.sendSoilMoistureData(soilMoistureValue, soilMoisturePercent);

  influxDBManager.sendWiFiData(WiFi.RSSI(), WiFi.channel(), WiFi.localIP().toString().c_str());

  strategy.setCurrentPercent(soilMoisturePercent);
  wateringManager.waterIfNeeded();

  delay(8000);
}

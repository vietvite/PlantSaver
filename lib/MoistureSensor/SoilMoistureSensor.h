#include <Adafruit_GFX.h>

class SoilMoistureSensor
{
public:
    SoilMoistureSensor(int sensorPin, int airValue, int waterValue)
        : sensorPin(sensorPin), airValue(airValue), waterValue(waterValue) {}

    int readSoilMoisture()
    {
        int soilMoistureValue = analogRead(sensorPin);
        Serial.println(soilMoistureValue);
        return soilMoistureValue;
    }

    int calculatePercentage(int soilMoistureValue)
    {
        return map(soilMoistureValue, airValue, waterValue, 0, 100);
    }

private:
    int sensorPin;
    int airValue;
    int waterValue;
};
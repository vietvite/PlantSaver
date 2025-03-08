#include "UnderThresholdStrategy.h"
#include <Arduino.h>

UnderThresholdStrategy::UnderThresholdStrategy(int threshold, int wateringDuration) 
  : threshold(threshold), currentSoilMoisturePercent(100), wateringDuration(wateringDuration) {}

void UnderThresholdStrategy::setCurrentPercent(int value) {
  currentSoilMoisturePercent = value;
}

void UnderThresholdStrategy::water(int relayPin) {
  if (currentSoilMoisturePercent < threshold) {
    Serial.println("Soil moisture below threshold. Starting watering...");
    digitalWrite(relayPin, HIGH); // Turn on the relay
    delay(wateringDuration);      // Keep the relay on for the specified duration
    digitalWrite(relayPin, LOW);  // Turn off the relay
    Serial.println("Watering completed.");
  } else {
    Serial.println("Soil moisture above threshold. No watering needed.");
  }
}

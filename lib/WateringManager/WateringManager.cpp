#include "WateringManager.h"

WateringManager::WateringManager(int relayPin, WateringStrategy* strategy) : relayPin(relayPin), strategy(strategy) {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Ensure the relay is off initially
}

void WateringManager::waterIfNeeded() {
  strategy->water(relayPin);
}

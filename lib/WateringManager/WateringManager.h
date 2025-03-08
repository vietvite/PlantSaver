#ifndef WATERING_MANAGER_H
#define WATERING_MANAGER_H

#include <Arduino.h>
#include "WateringStrategy.h"

class WateringManager {
public:
  WateringManager(int relayPin, WateringStrategy* strategy);
  void waterIfNeeded();

private:
  int relayPin;
  WateringStrategy* strategy;
};

#endif // WATERING_MANAGER_H

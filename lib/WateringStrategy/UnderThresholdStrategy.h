#ifndef UNDER_THRESHOLD_STRATEGY_H
#define UNDER_THRESHOLD_STRATEGY_H

#include "WateringStrategy.h"

class UnderThresholdStrategy : public WateringStrategy {
public:
  UnderThresholdStrategy(int threshold = 10, int wateringDuration = 30000);
  void setCurrentPercent(int value);
  void water(int relayPin) override;

private:
  int threshold;
  int currentSoilMoisturePercent;
  int wateringDuration;
};

#endif // UNDER_THRESHOLD_STRATEGY_H

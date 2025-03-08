#ifndef WATERING_STRATEGY_H
#define WATERING_STRATEGY_H

class WateringStrategy {
public:
  virtual void water(int relayPin) = 0;
};

#endif // WATERING_STRATEGY_H

#include <assert.h>
#include <iostream>
using namespace std;

enum class RangeStatus { OK, LOW, HIGH };

// Generic function to check range and return status
RangeStatus checkRange(float value, float min, float max) {
  if (value < min) {
    return RangeStatus::LOW;
  }
  if (value > max) {
    return RangeStatus::HIGH;
  }
  return RangeStatus::OK;
}

// Specific range check functions using the generic function
RangeStatus checkTemperature(float temperature) {
  return checkRange(temperature, 0, 45);
}

RangeStatus checkSoc(float soc) {
  return checkRange(soc, 20, 80);
}

RangeStatus checkChargeRate(float chargeRate) {
  return checkRange(chargeRate, 0, 0.8);
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
  return checkTemperature(temperature) == RangeStatus::OK &&
         checkSoc(soc) == RangeStatus::OK &&
         checkChargeRate(chargeRate) == RangeStatus::OK;
}

// Generic function to print status messages
void printStatusMessage(const char* parameterName, RangeStatus status) {
  if (status == RangeStatus::LOW) {
    cout << parameterName << " is too low!\n";
  } else if (status == RangeStatus::HIGH) {
    cout << parameterName << " is too high!\n";
  }
}

// Specific status print functions using the generic function
void printTemperatureStatus(float temperature) {
  printStatusMessage("Temperature", checkTemperature(temperature));
}

void printSocStatus(float soc) {
  printStatusMessage("State of Charge", checkSoc(soc));
}

void printChargeRateStatus(float chargeRate) {
  printStatusMessage("Charge Rate", checkChargeRate(chargeRate));
}

void printBatteryStatus(float temperature, float soc, float chargeRate) {
  printTemperatureStatus(temperature);
  printSocStatus(soc);
  printChargeRateStatus(chargeRate);
}

int main() {
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(50, 85, 0) == false);

  // Testing with print statements
  printBatteryStatus(25, 70, 0.7);  // Should print nothing
  printBatteryStatus(50, 85, 0);    // Should print messages for temperature and soc
}

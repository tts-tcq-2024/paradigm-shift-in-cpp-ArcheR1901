#include <assert.h>
#include <iostream>
#include <map>
#include <tuple>
using namespace std;

enum class RangeStatus { OK, LOW, HIGH, WARNING };

enum class Language { ENGLISH, GERMAN };

// Global variable to hold the current language setting
Language currentLanguage = Language::ENGLISH;

// Function to get the warning tolerance
float getWarningTolerance(float max) {
    return 0.05f * max;
}

// Generic function to check range and return status
RangeStatus checkRange(float value, float min, float max) {
    float tolerance = getWarningTolerance(max);
    if (value < min) return RangeStatus::LOW;
    if (value > max) return RangeStatus::HIGH;
    if (value < min + tolerance || value > max - tolerance) return RangeStatus::WARNING;
    return RangeStatus::OK;
}

// Function to perform the check and message printing
void checkAndPrintStatus(const char* parameterName, float value, float min, float max) {
    RangeStatus status = checkRange(value, min, max);
    static map<Language, map<RangeStatus, map<const char*, const char*>>> messages = {
        { Language::ENGLISH, {
                { RangeStatus::LOW, { { "Temperature", "Temperature is too low!\n" },
                                      { "State of Charge", "State of Charge is too low!\n" },
                                      { "Charge Rate", "Charge Rate is too low!\n" } } },
                { RangeStatus::HIGH, { { "Temperature", "Temperature is too high!\n" },
                                       { "State of Charge", "State of Charge is too high!\n" },
                                       { "Charge Rate", "Charge Rate is too high!\n" } } },
                { RangeStatus::WARNING, { { "Temperature", "Warning: Temperature is approaching limit!\n" },
                                          { "State of Charge", "Warning: State of Charge is approaching limit!\n" },
                                          { "Charge Rate", "Warning: Charge Rate is approaching limit!\n" } } }
            }
        },
        { Language::GERMAN, {
                { RangeStatus::LOW, { { "Temperature", "Temperatur ist zu niedrig!\n" },
                                      { "State of Charge", "Ladezustand ist zu niedrig!\n" },
                                      { "Charge Rate", "Laderate ist zu niedrig!\n" } } },
                { RangeStatus::HIGH, { { "Temperature", "Temperatur ist zu hoch!\n" },
                                       { "State of Charge", "Ladezustand ist zu hoch!\n" },
                                       { "Charge Rate", "Laderate ist zu hoch!\n" } } },
                { RangeStatus::WARNING, { { "Temperature", "Warnung: Temperatur nähert sich dem Grenzwert!\n" },
                                          { "State of Charge", "Warnung: Ladezustand nähert sich dem Grenzwert!\n" },
                                          { "Charge Rate", "Warnung: Laderate nähert sich dem Grenzwert!\n" } } }
            }
        }
    };
    if (status != RangeStatus::OK) {
        cout << messages[currentLanguage][status][parameterName];
    }
}

// Function to check and print all battery statuses
void printBatteryStatus(float temperature, float soc, float chargeRate) {
    checkAndPrintStatus("Temperature", temperature, 0, 45);
    checkAndPrintStatus("State of Charge", soc, 20, 80);
    checkAndPrintStatus("Charge Rate", chargeRate, 0, 0.8);
}

int main() {
    // Test cases
    assert(batteryIsOk(25, 70, 0.7) == true);
    assert(batteryIsOk(50, 85, 0) == false);

    // Testing with print statements in English
    currentLanguage = Language::ENGLISH;
    printBatteryStatus(25, 70, 0.7);  // Should print nothing
    printBatteryStatus(50, 85, 0);    // Should print messages for temperature and soc

    // Testing with print statements in German
    currentLanguage = Language::GERMAN;
    printBatteryStatus(25, 70, 0.7);  // Should print nothing
    printBatteryStatus(50, 85, 0);    // Should print messages for temperature and soc

    return 0;
}

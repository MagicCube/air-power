#include "Settings.h"

#include <EEPROM.h>

#include "../utils/format.h"
#include "log.h"

void Settings::begin() {
  LOG_I("Loading settings from EEPROM...");
  EEPROM.begin(7);
  LOG_D("Reading previous settings from EEPROM...");
  if (EEPROM.read(0)) {
    bool _clientAddressAvailable = false;
    for (int i = 0; i < 6; i++) {
      _clientAddress[i] = EEPROM.read(i + 1);
      if (_clientAddress[i] != 255 && _clientAddress != 0) {
        _clientAddressAvailable = true;
      }
    }
    if (_clientAddressAvailable) {
      _hasClientAddress = true;
    }
  }
  if (_hasClientAddress) {
    LOG_D("Saved client address was found: [%s]", formatBLEAddress(_clientAddress).c_str());
  } else {
    LOG_D("No previous setting wa found in EEPROM.");
  }
}

bool Settings::hasClientAddress() {
  return _hasClientAddress;
}

ble_address_t Settings::clientAddress() {
  return _clientAddress;
}

void Settings::clientAddress(ble_address_t value) {
  LOG_D("[EEPROM] sets client address.");
  _touch();
  for (int i = 0; i < 6; i++) {
    EEPROM.write(i + 1, value[i]);
  }
  _hasClientAddress = true;
}

void Settings::save() {
  EEPROM.commit();
  LOG_D("[EEPROM] has been <SAVED>.");
}

void Settings::_touch() {
  EEPROM.write(0, 1);
}

Settings AirChargerSettings;

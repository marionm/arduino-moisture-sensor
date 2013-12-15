#include "notifier.h"

#include <SPI.h>

#include "Adafruit_CC3000.h"
#include "menu/settings.h"

Notifier::Notifier(
  byte _nameSettingsIndex,
  byte _emailSettingsIndex,
  byte _phoneSettingsIndex,
  byte _earliestTimeSettingsIndex,
  byte _latestTimeSettingsIndex,
  byte _ssidSettingsIndex,
  byte _usernameSettingsIndex,
  byte _passwordSettingsIndex
) {
  nameSettingsIndex         = _nameSettingsIndex;
  emailSettingsIndex        = _emailSettingsIndex;
  phoneSettingsIndex        = _phoneSettingsIndex;
  earliestTimeSettingsIndex = _earliestTimeSettingsIndex;
  latestTimeSettingsIndex   = _latestTimeSettingsIndex;
  ssidSettingsIndex         = _ssidSettingsIndex;
  usernameSettingsIndex     = _usernameSettingsIndex;
  passwordSettingsIndex     = _passwordSettingsIndex;

  byte csPin   = 10;
  byte irqPin  =  3;
  byte vbatPin =  5;
  wifi = new Adafruit_CC3000(csPin, irqPin, vbatPin, SPI_CLOCK_DIV2);

  connected = false;
}

Notifier::~Notifier() {
  delete wifi;
}

boolean Notifier::testConnection() {
  connect();

  // TODO
  boolean success = false;

  disconnect();
  return success;
}

void Notifier::sendNotificationIfInWindow() {
  if(inNotificationWindow()) {
    if(!connected) {
      connect();
    }
  }

  if(connected) {
    disconnect();
  }
}

boolean Notifier::inNotificationWindow() {
  String earliest = MenuSettings::getValue(earliestTimeSettingsIndex);
  String latest   = MenuSettings::getValue(latestTimeSettingsIndex);

  // TODO
  byte hour = 12;

  return hour >= earliest.toInt() && hour <= latest.toInt();
}

void Notifier::connect() {
  connected = true;
  // TODO
}

void Notifier::disconnect() {
  connected = false;
  // TODO
}

#include "notifier.h"

#include <SPI.h>

#include "menu/settings.h"

Notifier::Notifier(
  byte _nameSettingsIndex,
  byte _emailSettingsIndex,
  byte _phoneSettingsIndex,
  byte _earliestTimeSettingsIndex,
  byte _latestTimeSettingsIndex,
  byte _ssidSettingsIndex,
  byte _passwordSettingsIndex
) {
  nameSettingsIndex         = _nameSettingsIndex;
  emailSettingsIndex        = _emailSettingsIndex;
  phoneSettingsIndex        = _phoneSettingsIndex;
  earliestTimeSettingsIndex = _earliestTimeSettingsIndex;
  latestTimeSettingsIndex   = _latestTimeSettingsIndex;
  ssidSettingsIndex         = _ssidSettingsIndex;
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

boolean Notifier::testConnection(Adafruit_RGBLCDShield *lcd) {
  if(lcd) {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print(F("Connecting..."));
  }

  byte result = connect();

  if(lcd) {
    lcd->clear();
    lcd->setCursor(0, 0);

    if(result == 0) {
      uint32_t addr, netmask, gateway, dhcpServer, dnsServer;
      wifi->getIPAddress(&addr, &netmask, &gateway, &dhcpServer, &dnsServer);

      lcd->print(F("Success!"));
      lcd->setCursor(0, 1);
      lcd->print(addr);
    } else {
      lcd->print(F("Failed"));
      lcd->setCursor(0, 1);
      if(result == 1) {
        lcd->print(F("Board init error"));
      } else if(result == 2) {
        lcd->print(F("Couldn't connect"));
      } else if(result == 3) {
        lcd->print(F("DCHP timeout"));
      } else if(result == 4) {
        lcd->print(F("Unknown reason"));
      }
    }
  }
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

byte Notifier::connect() {
  if(!wifi->begin()) {
    return 1;
  }
  if(!wifi->deleteProfiles()) {
    return 2;
  }

  String ssidString = MenuSettings::getValue(ssidSettingsIndex);
  char ssid[ssidString.length() + 1];
  ssidString.toCharArray(ssid, 0, ssidString.length());
  String passwordString = MenuSettings::getValue(passwordSettingsIndex);
  char password[passwordString.length() + 1];
  passwordString.toCharArray(ssid, 0, passwordString.length());
  byte security   = WLAN_SEC_WPA2;
  if(!wifi->connectToAP(ssid, password, security)) {
    return 3;
  }

  long startTime = millis();
  long timeout   = 60000;
  while(!wifi->checkDHCP() && (millis() - startTime) < timeout);
  if(!wifi->checkDHCP()) {
    return 4;
  }

  connected = true;
  return 0;
}

void Notifier::disconnect() {
  // TODO
  // connected = false;
}

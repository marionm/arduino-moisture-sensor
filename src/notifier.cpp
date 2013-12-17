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

boolean Notifier::testConnection(char resultMessage[16]) {
  byte result = connect();

  switch(result) {
    case 0:
      uint32_t addr, netmask, gateway, dhcpserv, dnsserv;
      if(wifi->getIPAddress(&addr, &netmask, &gateway, &dhcpserv, &dnsserv)) {
        String ip = String((byte)(addr >> 24)) +
          "." + String((byte)(addr >> 16)) +
          "." + String((byte)(addr >> 8)) +
          "." + String((byte)(addr));
        ip.toCharArray(resultMessage, ip.length() + 1);
      } else {
        strcpy(resultMessage, "No IP address");
        result = 5;
      }
      break;
    case 1:
      strcpy(resultMessage, "Board init error");
      break;
    case 2:
      strcpy(resultMessage, "Couldn't reset");
      break;
    case 3:
      strcpy(resultMessage, "Couldn't connect");
      break;
    case 4:
      strcpy(resultMessage, "DHCP timeout");
      break;
    default:
      strcpy(resultMessage, "Unknown error");
      break;
  }

  if(connected) {
    disconnect();
  }

  return result == 0;
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
  ssidString.toCharArray(ssid, ssidString.length() + 1);

  String passwordString = MenuSettings::getValue(passwordSettingsIndex);
  char password[passwordString.length() + 1];
  passwordString.toCharArray(password, passwordString.length() + 1);

  byte security = WLAN_SEC_WPA2;
  byte connectedToAP = wifi->connectToAP(ssid, password, security);
  if(!connectedToAP) {
    return 3;
  }

  long time = millis();
  while(!wifi->checkDHCP() && (millis() - time) < 60000L);
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

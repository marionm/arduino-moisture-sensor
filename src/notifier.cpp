#include "notifier.h"

#include <SPI.h>

#include "credentials.h"
#include "menu/settings.h"
#include "settings.h"

Notifier::Notifier() {
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

void Notifier::sendNotificationsIfInWindow() {
  boolean disconnectNow = false;
  if(inNotificationWindow()) {
    if(!connected) {
      connect();
      disconnectNow = true;
    }
  }

  if(disconnectNow) {
    disconnect();
  }
}

boolean Notifier::inNotificationWindow() {
  String earliest = MenuSettings::getValue(EARLIEST_ID);
  String latest   = MenuSettings::getValue(LATEST_ID);

  // TODO
  byte hour = 12;

  return hour >= earliest.toInt() && hour <= latest.toInt();
}

void Notifier::sendEmail() {
  boolean disconnectNow = false;
  if(!connected) {
    connect();
    disconnectNow = true;
  }

  unsigned long ip;
  wifi->getHostByName("smtpcorp.com", &ip);

  long startTime = millis();
  Adafruit_CC3000_Client client;
  do {
    client = wifi->connectTCP(ip, 2525);
  } while(!client.connected() && (millis() - startTime) < 5000L);

  if(client.connected()) {
    // TODO: Support input > 16 characters and drop hardcoded @gmail.com
    String name  = MenuSettings::getValue(NAME_ID);
    String email = MenuSettings::getValue(EMAIL_ID);
    client.print(F("helo 192.168.1.1\r\n"));

    client.print(String("MAIL From: <") + SMTP2GO_EMAIL + ">\r\n");
    client.print("RCPT To: <" + email + "@gmail.com>\r\n");
    client.print(F("DATA\r\n"));
    client.print(String("From:Secret Project <") + SMTP2GO_EMAIL + ">\r\n");
    client.print("To:<" + email + "@gmail.com>\r\n");

    client.print("Subject:" + name + "\r\n");
    client.print(name + "\r\n");

    client.print(F(".\r\n"));
    client.print(F("QUIT\r\n"));
  }

  if(disconnectNow) {
    disconnect();
  }
}

void Notifier::sendText() {
  boolean disconnectNow = false;
  if(!connected) {
    connect();
    disconnectNow = true;
  }

  // TODO

  if(disconnectNow) {
    disconnect();
  }
}

byte Notifier::connect() {
  if(!wifi->begin()) {
    return 1;
  }

  if(!wifi->deleteProfiles()) {
    return 2;
  }

  String ssidString = MenuSettings::getValue(SSID_ID);
  char ssid[ssidString.length() + 1];
  ssidString.toCharArray(ssid, ssidString.length() + 1);

  String passwordString = MenuSettings::getValue(PASSWORD_ID);
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

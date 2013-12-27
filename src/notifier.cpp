#include "notifier.h"

#include <SPI.h>

#include "credentials.h"
#include "menu/settings.h"
#include "menu/util.h"
#include "settings.h"

Notifier::Notifier() {
  byte csPin   = 10;
  byte irqPin  =  3;
  byte vbatPin =  5;
  wifi = new Adafruit_CC3000(csPin, irqPin, vbatPin, SPI_CLOCK_DIV2);

  // TODO: Use wifi->connected() instead, if it works as expected
  connected = false;
}

Notifier::~Notifier() {
  delete wifi;
}

boolean Notifier::testConnection(char resultMessage[17]) {
  byte result = connect();

  switch(result) {
    case 0:
      uint32_t addr, netmask, gateway, dhcpserv, dnsserv;
      if(wifi->getIPAddress(&addr, &netmask, &gateway, &dhcpserv, &dnsserv)) {
        strcpy(resultMessage, "IP acquired");
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

boolean Notifier::sendNotificationsIfInWindow() {
  if(!inNotificationWindow()) return false;
  if(!connected && connect() != 0) return false;

  sendEmail();
  sendText();

  disconnect();

  return true;
}

boolean Notifier::inNotificationWindow() {
  if(connect() != 0) {
    return false;
  }

  byte earliest = MenuUtil::stringToByte(MenuSettings::getValue(EARLIEST_ID));
  byte latest   = MenuUtil::stringToByte(MenuSettings::getValue(LATEST_ID));

  // TODO
  byte hour = 12;

  if(hour >= earliest && hour <= latest) {
    return true;
  } else {
    disconnect();
    return false;
  }
}

void Notifier::sendEmail() {
  boolean disconnectNow = false;
  if(!connected) {
    if(connect() != 0) return;
    disconnectNow = true;
  }

  Adafruit_CC3000_Client client = connectToHost("smtpcorp.com", 2525);
  if(client.connected()) {
    // TODO: Support input > 16 characters and drop hardcoded @gmail.com
    char name[MENU_STORAGE_SIZE];
    char email[MENU_STORAGE_SIZE];
    strcpy(name,  MenuSettings::getValue(NAME_ID));
    strcpy(email, MenuSettings::getValue(EMAIL_ID));

    client.print(F("helo 192.168.1.1\r\n"));

    client.print(F("MAIL From: <")); client.print(SMTP2GO_EMAIL); client.print(F(">\r\n"));
    client.print(F("RCPT To: <")); client.print(email); client.print(F("@gmail.com>\r\n"));
    client.print(F("DATA\r\n"));
    client.print(F("From:Secret Project <")); client.print(SMTP2GO_EMAIL); client.print(F(">\r\n"));
    client.print(F("To:<")); client.print(email); client.print(F("@gmail.com>\r\n"));

    client.print(F("Subject:")); client.print(F("I'm thirsty!")); client.print(F("\r\n"));
    client.print(F("Water needed for: ")); client.print(name); client.print(F("\r\n"));

    client.print(F(".\r\n"));
    client.print(F("QUIT\r\n"));
  }

  if(disconnectNow) {
    disconnect();
  }
}

void Notifier::sendText() {
  char phoneNumber[MENU_STORAGE_SIZE];
  strcpy(phoneNumber, MenuSettings::getValue(PHONE_ID));
  if(strlen(phoneNumber) != 10) return;

  boolean disconnectNow = false;
  if(!connected) {
    if(connect() != 0) return;
    disconnectNow = true;
  }

  Adafruit_CC3000_Client client = connectToHost("txtdrop.com");
  if(client.connected()) {
    char name[MENU_STORAGE_SIZE];
    strcpy(name, MenuSettings::getValue(NAME_ID));

    int contentLength = 100;
    contentLength += strlen(name);

    char content[contentLength];
    strcpy(content, "submitted=1&submit=Send&body=I%27m%20thirst&emailfrom=");
    strcat(content, name);
    strcat(content, "%40garden.com");

    byte i = 0;
    byte j = 67 + strlen(name);
    strcat(content, "&npa=");
    for(j +=  5; i <  3; i++, j++) { content[j] = phoneNumber[i]; }
    strcat(content, "&exchange=");
    for(j += 10; i <  6; i++, j++) { content[j] = phoneNumber[i]; }
    strcat(content, "&number=");
    for(j +=  8; i < 10; i++, j++) { content[j] = phoneNumber[i]; }

    client.println(F("POST http://www.txtdrop.com HTTP/1.1"));
    client.println(F("Host: www.txtdrop.com"));
    client.println(F("Connection: close"));
    client.print(  F("Content-Length: ")); client.println(contentLength);
    client.println();
    client.println(content);
  }

  if(disconnectNow) {
    disconnect();
  }
}

byte Notifier::connect() {
  if(!wifi->begin()) {
    return 1;
  }

  if(!wifi->deleteProfiles()) {
    wifi->stop();
    return 2;
  }

  char ssid[MENU_STORAGE_SIZE];
  char password[MENU_STORAGE_SIZE];
  strcpy(ssid ,    MenuSettings::getValue(SSID_ID));
  strcpy(password, MenuSettings::getValue(PASSWORD_ID));

  byte security = WLAN_SEC_WPA2;
  byte connectedToAP = wifi->connectToAP(ssid, password, security);
  if(!connectedToAP) {
    wifi->stop();
    return 3;
  }

  long time = millis();
  while(!wifi->checkDHCP() && (millis() - time) < 60000L);
  if(!wifi->checkDHCP()) {
    wifi->stop();
    return 4;
  }

  connected = true;
  return 0;
}

Adafruit_CC3000_Client Notifier::connectToHost(char *host, int port) {
  Adafruit_CC3000_Client client;

  if(connected) {
    unsigned long ip;
    wifi->getHostByName(host, &ip);

    long startTime = millis();
    do {
      client = wifi->connectTCP(ip, port);
    } while(!client.connected() && (millis() - startTime) < 5000L);
  }

  return client;
}

void Notifier::disconnect() {
  wifi->stop();
  connected = false;
}

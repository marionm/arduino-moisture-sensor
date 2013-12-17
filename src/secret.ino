#include <Arduino.h>

#include "notifier.h"
#include "menu/menu.h"

#define NAME_ID      0
#define THRESHOLD_ID 1
#define EMAIL_ID     2
#define PHONE_ID     3
#define EARLIEST_ID  4
#define LATEST_ID    5
#define SSID_ID      6
#define PASSWORD_ID  8

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
MenuDisplay menu = MenuDisplay(&lcd);

Notifier notifier = Notifier(NAME_ID, EMAIL_ID, PHONE_ID, EARLIEST_ID, LATEST_ID, SSID_ID, PASSWORD_ID);

void setup() {
  MenuTier *home = new MenuTier(F("Home"));
  new MenuOutput(F("Check now"), home, getSecretValue);

  MenuTier *settings = new MenuTier(F("Settings"), home);
  new TextMenuInput   (F("Name"),      settings, NAME_ID);
  new NumericMenuInput(F("Threshold"), settings, THRESHOLD_ID);

  MenuTier *notifications = new MenuTier(F("Notifications"), settings);
  new TextMenuInput   (F("E-mail"),        notifications, EMAIL_ID, EMAIL_CHARACTER_SET);
  new TextMenuInput   (F("Phone number"),  notifications, PHONE_ID, NUMERIC_CHARACTER_SET);
  new NumericMenuInput(F("Earliest time"), notifications, EARLIEST_ID, 0, 23);
  new NumericMenuInput(F("Latest time"),   notifications, LATEST_ID, 0, 23);

  MenuTier *wireless = new MenuTier(F("Wireless"), settings);
  new TextMenuInput (F("SSID"),          wireless, SSID_ID,     FULL_CHARACTER_SET);
  new TextMenuInput (F("Password"),      wireless, PASSWORD_ID, FULL_CHARACTER_SET);
  new MenuOutput    (F("Test wireless"), wireless, testWireless);

  menu.enable(home);
}

void loop() {
  menu.render();

  byte value = getSecretValue().toInt();
  byte threshold = MenuSettings::getValue(THRESHOLD_ID).toInt();
  if(value <= threshold) {
    // notifier.sendNotificationIfInWindow();
  }
}

String getSecretValue() {
  return "TODO";
}

String testWireless() {
  boolean success = notifier.testConnection(&lcd);
  if(success) {
    return "OK";
  } else {
    return "Failed";
  }
  return "Failed";
}

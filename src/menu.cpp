#include "menu.h"
#include "settings.h"

MenuEntry* Menu::home() {
  return new MenuTier((byte)2, homeChild, homeChildName);
}

__FlashStringHelper* Menu::homeChildName(byte i) {
  switch(i) {
    case 0: return F("Check Now");
    case 1: return F("Settings");
  }
  return NULL;
}

MenuEntry* Menu::homeChild(byte i) {
  switch(i) {
    case 0: return new MenuOutput(homeChildName(i), home, printMoistureLevel);
    case 1: return settings();
  }
  return NULL;
}

MenuEntry* Menu::settings() {
  return new MenuTier(4, settingsChild, settingsChildName, home);
}

__FlashStringHelper* Menu::settingsChildName(byte i) {
  switch(i) {
    case 0: return F("Name");
    case 1: return F("Threshold");
    case 2: return F("Notifications");
    case 3: return F("Wireless");
  }
  return NULL;
}

MenuEntry* Menu::settingsChild(byte i) {
  switch(i) {
    case 0: return new TextMenuInput   (settingsChildName(i), settings, NAME_ID);
    case 1: return new NumericMenuInput(settingsChildName(i), settings, THRESHOLD_ID);
    case 2: return notifications();
    case 3: return wireless();
  }
  return NULL;
}

MenuEntry* Menu::notifications() {
  return new MenuTier(4, notificationsChild, notificationsChildName, settings);
}

__FlashStringHelper* Menu::notificationsChildName(byte i) {
  switch(i) {
    case 0: return F("Gmail Address");
    case 1: return F("Phone number");
    case 2: return F("Earliest time");
    case 3: return F("Latest time");
  }
  return NULL;
}

MenuEntry* Menu::notificationsChild(byte i) {
  __FlashStringHelper *name = settingsChildName(i);
  switch(i) {
    case 0: return new TextMenuInput   (name, notifications, EMAIL_ID, EMAIL_CHARACTER_SET);
    case 1: return new TextMenuInput   (name, notifications, PHONE_ID, NUMERIC_CHARACTER_SET);
    case 2: return new NumericMenuInput(name, notifications, EARLIEST_ID, 0, 23);
    case 3: return new NumericMenuInput(name, notifications, LATEST_ID, 0, 23);
  }
  return NULL;
}

MenuEntry* Menu::wireless() {
  return new MenuTier(3, wirelessChild, wirelessChildName, settings);
}

__FlashStringHelper* Menu::wirelessChildName(byte i) {
  switch(i) {
    case 0: return F("SSID");
    case 1: return F("Password");
    case 2: return F("Test wireless");
  }
  return NULL;
}

MenuEntry* Menu::wirelessChild(byte i) {
  __FlashStringHelper *name = settingsChildName(i);
  switch(i) {
    case 0: return new TextMenuInput (name, wireless, SSID_ID,     FULL_CHARACTER_SET);
    case 1: return new TextMenuInput (name, wireless, PASSWORD_ID, FULL_CHARACTER_SET);
    case 2: return new MenuOutput    (name, wireless, testWireless);
  }
  return NULL;
}

void Menu::printMoistureLevel(void **args) {
  Adafruit_RGBLCDShield *lcd = (Adafruit_RGBLCDShield*)args[0];

  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print(F("Reading..."));

  int value = Sensor::read();

  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print(F("Current value:"));

  lcd->setCursor(0, 1);
  lcd->print(value);
}

void Menu::testWireless(void **args) {
  Adafruit_RGBLCDShield **lcdArgs = (Adafruit_RGBLCDShield**)args;
  Adafruit_RGBLCDShield *lcd = (Adafruit_RGBLCDShield*)lcdArgs[0];
  Notifier *notifier = (Notifier*)lcdArgs[1];

  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print(F("Connecting..."));

  char result[17];
  boolean success = notifier->testConnection(result);

  lcd->clear();
  lcd->setCursor(0, 0);
  if(success) {
    lcd->print(F("Connected"));
  } else {
    lcd->print(F("Failed"));
  }
  lcd->setCursor(0, 1);
  lcd->print(result);

  delay(5000L);
}

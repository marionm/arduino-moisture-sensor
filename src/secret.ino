#include <Arduino.h>

#include "notifier.h"
#include "menu/menu.h"
#include "settings.h"

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
MenuDisplay menu = MenuDisplay(&lcd);

Notifier notifier = Notifier();

void setup() {
  MenuTier *home = new MenuTier(F("Home"));
  new MenuOutput(F("Check now"), home, printSecretValue);

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

void printSecretValue(Adafruit_RGBLCDShield *lcd) {
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print(getSecretValue());
}

void testWireless(Adafruit_RGBLCDShield *lcd) {
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print(F("Connecting..."));

  char result[16];
  boolean success = notifier.testConnection(result);

  lcd->clear();
  lcd->setCursor(0, 0);
  if(success) {
    lcd->print(F("Connected"));
  } else {
    lcd->print(F("Failed"));
  }
  lcd->setCursor(0, 1);
  lcd->print(result);
}

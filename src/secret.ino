#include <Arduino.h>

#include "menu/menu.h"
#include "menu/eeprom_settings.h"

#define NAME_ID      0
#define THRESHOLD_ID 1
#define EMAIL_ID     2
#define PHONE_ID     3
#define EARLIEST_ID  4
#define LATEST_ID    5
#define SSID_ID      6
#define USERNAME_ID  7
#define PASSWORD_ID  8

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
MenuDisplay menu = MenuDisplay(&lcd);

void setup() {
  MenuTier *home = new MenuTier("Home");
  new MenuOutput("Check now", home, getSecretValue);

  MenuTier *settings = new MenuTier("Settings", home);
  new TextMenuInput   ("Name",      settings, new EEPROMMenuSettings(NAME_ID));
  new NumericMenuInput("Threshold", settings, new EEPROMMenuSettings(THRESHOLD_ID));

  MenuTier *notifications = new MenuTier("Notifications", settings);
  new TextMenuInput   ("E-mail",        notifications, new EEPROMMenuSettings(EMAIL_ID), EMAIL_CHARACTER_SET);
  new TextMenuInput   ("Phone number",  notifications, new EEPROMMenuSettings(PHONE_ID), NUMERIC_CHARACTER_SET);
  new NumericMenuInput("Earliest time", notifications, new EEPROMMenuSettings(EARLIEST_ID), 0, 23);
  new NumericMenuInput("Latest time",   notifications, new EEPROMMenuSettings(LATEST_ID), 0, 23);

  MenuTier *wireless = new MenuTier("Wireless", settings);
  new TextMenuInput ("SSID",          wireless, new EEPROMMenuSettings(SSID_ID),     FULL_CHARACTER_SET);
  new TextMenuInput ("Username",      wireless, new EEPROMMenuSettings(USERNAME_ID), FULL_CHARACTER_SET);
  new TextMenuInput ("Password",      wireless, new EEPROMMenuSettings(PASSWORD_ID), FULL_CHARACTER_SET);
  new MenuOutput    ("Test wireless", wireless, getSecretValue);

  menu.enable(home);
}

void loop() {
  menu.render();
}

String getSecretValue() {
  return "TODO";
}

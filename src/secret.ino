#include <Arduino.h>

#include "menu/menu.h"
#include "menu/eeprom_settings.h"

#define NAME_BLOCK      0
#define THRESHOLD_BLOCK 1
#define EMAIL_BLOCK     2
#define PHONE_BLOCK     3
#define EARLIEST_BLOCK  4
#define LATEST_BLOCK    5
#define SSID_BLOCK      6
#define USERNAME_BLOCK  7
#define PASSWORD_BLOCK  8

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
MenuDisplay menu = MenuDisplay(&lcd);

void setup() {
  MenuTier *home = new MenuTier("Home");
  new MenuOutput("Check now", home, getSecretValue);

  MenuTier *settings = new MenuTier("Settings", home);
  new MenuInput("Name",      settings, new EEPROMMenuSettings(NAME_BLOCK));
  new MenuInput("Threshold", settings, new EEPROMMenuSettings(THRESHOLD_BLOCK));

  MenuTier *notifications = new MenuTier("Notifications", settings);
  new MenuInput("E-mail",        notifications, new EEPROMMenuSettings(EMAIL_BLOCK));
  new MenuInput("Phone number",  notifications, new EEPROMMenuSettings(PHONE_BLOCK));
  new MenuInput("Earliest time", notifications, new EEPROMMenuSettings(EARLIEST_BLOCK));
  new MenuInput("Latest time",   notifications, new EEPROMMenuSettings(LATEST_BLOCK));

  MenuTier *wireless = new MenuTier("Wireless", settings);
  new MenuInput ("SSID",          wireless, new EEPROMMenuSettings(SSID_BLOCK));
  new MenuInput ("Username",      wireless, new EEPROMMenuSettings(USERNAME_BLOCK));
  new MenuInput ("Password",      wireless, new EEPROMMenuSettings(PASSWORD_BLOCK));
  new MenuOutput("Test wireless", wireless, getSecretValue);

  menu.enable(home);
}

void loop() {
  menu.render();
}

String getSecretValue() {
  return "TODO";
}

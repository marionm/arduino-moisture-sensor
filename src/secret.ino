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

#define NUMERIC_CHARACTER_SET &MenuInput::CharacterSets::numeric
#define EMAIL_CHARACTER_SET   &MenuInput::CharacterSets::email
#define FULL_CHARACTER_SET    &MenuInput::CharacterSets::full

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
MenuDisplay menu = MenuDisplay(&lcd);

void setup() {
  MenuTier *home = new MenuTier("Home");
  new MenuOutput("Check now", home, getSecretValue);

  MenuTier *settings = new MenuTier("Settings", home);
  new MenuInput("Name",      settings, new EEPROMMenuSettings(NAME_BLOCK));
  new MenuInput("Threshold", settings, new EEPROMMenuSettings(THRESHOLD_BLOCK), NUMERIC_CHARACTER_SET);

  MenuTier *notifications = new MenuTier("Notifications", settings);
  new MenuInput("E-mail",        notifications, new EEPROMMenuSettings(EMAIL_BLOCK),    EMAIL_CHARACTER_SET);
  new MenuInput("Phone number",  notifications, new EEPROMMenuSettings(PHONE_BLOCK),    NUMERIC_CHARACTER_SET);
  new MenuInput("Earliest time", notifications, new EEPROMMenuSettings(EARLIEST_BLOCK), NUMERIC_CHARACTER_SET);
  new MenuInput("Latest time",   notifications, new EEPROMMenuSettings(LATEST_BLOCK),   NUMERIC_CHARACTER_SET);

  MenuTier *wireless = new MenuTier("Wireless", settings);
  new MenuInput ("SSID",          wireless, new EEPROMMenuSettings(SSID_BLOCK),     FULL_CHARACTER_SET);
  new MenuInput ("Username",      wireless, new EEPROMMenuSettings(USERNAME_BLOCK), FULL_CHARACTER_SET);
  new MenuInput ("Password",      wireless, new EEPROMMenuSettings(PASSWORD_BLOCK), FULL_CHARACTER_SET);
  new MenuOutput("Test wireless", wireless, getSecretValue);

  menu.enable(home);
}

void loop() {
  menu.render();
}

String getSecretValue() {
  return "TODO";
}

#include <Arduino.h>

#include "menu/menu.h"

#define NAME_ID      0
#define THRESHOLD_ID 1
#define EMAIL_ID     2
#define PHONE_ID     3
#define EARLIEST_ID  4
#define LATEST_ID    5
#define SSID_ID      6
#define USERNAME_ID  7
#define PASSWORD_ID  8

#define SETTINGS_CLASS RAMMenuSettings

#define NUMERIC_CHARACTER_SET &MenuInput::CharacterSets::numeric
#define EMAIL_CHARACTER_SET   &MenuInput::CharacterSets::email
#define FULL_CHARACTER_SET    &MenuInput::CharacterSets::full

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
MenuDisplay menu = MenuDisplay(&lcd);

void setup() {
  MenuTier *home = new MenuTier("Home");
  new MenuOutput("Check now", home, getSecretValue);

  MenuTier *settings = new MenuTier("Settings", home);
  new MenuInput("Name",      settings, new SETTINGS_CLASS(NAME_ID));
  new MenuInput("Threshold", settings, new SETTINGS_CLASS(THRESHOLD_ID), NUMERIC_CHARACTER_SET);

  MenuTier *notifications = new MenuTier("Notifications", settings);
  new MenuInput("E-mail",        notifications, new SETTINGS_CLASS(EMAIL_ID),    EMAIL_CHARACTER_SET);
  new MenuInput("Phone number",  notifications, new SETTINGS_CLASS(PHONE_ID),    NUMERIC_CHARACTER_SET);
  new MenuInput("Earliest time", notifications, new SETTINGS_CLASS(EARLIEST_ID), NUMERIC_CHARACTER_SET);
  new MenuInput("Latest time",   notifications, new SETTINGS_CLASS(LATEST_ID),   NUMERIC_CHARACTER_SET);

  MenuTier *wireless = new MenuTier("Wireless", settings);
  new MenuInput ("SSID",          wireless, new SETTINGS_CLASS(SSID_ID),     FULL_CHARACTER_SET);
  new MenuInput ("Username",      wireless, new SETTINGS_CLASS(USERNAME_ID), FULL_CHARACTER_SET);
  new MenuInput ("Password",      wireless, new SETTINGS_CLASS(PASSWORD_ID), FULL_CHARACTER_SET);
  new MenuOutput("Test wireless", wireless, getSecretValue);

  menu.enable(home);
}

void loop() {
  menu.render();
}

String getSecretValue() {
  return "TODO";
}

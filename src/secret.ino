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

// TODO: Move into menu display directly
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
MenuDisplay menu = MenuDisplay(&lcd);

// TODO: Use just one shared settings object

void setup() {
  MenuTier *home = new MenuTier("Home");
  new MenuOutput("Check now", home, getSecretValue);

  MenuTier *settings = new MenuTier("Settings", home);
  new TextMenuInput   ("Name",      settings, NAME_ID);
  new NumericMenuInput("Threshold", settings, THRESHOLD_ID);

  MenuTier *notifications = new MenuTier("Notifications", settings);
  new TextMenuInput   ("E-mail",        notifications, EMAIL_ID, EMAIL_CHARACTER_SET);
  new TextMenuInput   ("Phone number",  notifications, PHONE_ID, NUMERIC_CHARACTER_SET);
  new NumericMenuInput("Earliest time", notifications, EARLIEST_ID, 0, 23);
  new NumericMenuInput("Latest time",   notifications, LATEST_ID, 0, 23);

  MenuTier *wireless = new MenuTier("Wireless", settings);
  new TextMenuInput ("SSID",          wireless, SSID_ID,     FULL_CHARACTER_SET);
  new TextMenuInput ("Username",      wireless, USERNAME_ID, FULL_CHARACTER_SET);
  new TextMenuInput ("Password",      wireless, PASSWORD_ID, FULL_CHARACTER_SET);
  new MenuOutput    ("Test wireless", wireless, testWireless);

  menu.enable(home);
}

void loop() {
  menu.render();
}

String getSecretValue() {
  return "TODO";
}

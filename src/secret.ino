#include <Arduino.h>

#include "menu/menu.h"

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
MenuDisplay menu = MenuDisplay(&lcd);

void setup() {
  MenuTier *home = new MenuTier("Home");
  new MenuOutput("Check now", home, getSecretValue);

  MenuTier *settings = new MenuTier("Settings", home);
  new MenuInput("Name",      settings);
  new MenuInput("Threshold", settings);

  MenuTier *notifications = new MenuTier("Notifications", settings);
  new MenuInput("E-mail",        notifications);
  new MenuInput("Phone number",  notifications);
  new MenuInput("Earliest time", notifications);
  new MenuInput("Latest time",   notifications);

  MenuTier *wireless = new MenuTier("Wireless", settings);
  new MenuInput ("SSID",          wireless);
  new MenuInput ("Username",      wireless);
  new MenuInput ("Password",      wireless);
  new MenuOutput("Test wireless", wireless, getSecretValue);

  menu.enable(home);
}

void loop() {
  menu.render();
}

String getSecretValue() {
  return "TODO";
}

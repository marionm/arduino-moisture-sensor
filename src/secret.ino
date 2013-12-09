#include <Wire.h>

#include "Adafruit_MCP23017.h"
#include "Adafruit_RGBLCDShield.h"

#include "MenuDisplay.h"
#include "MenuTier.h"
#include "MenuInput.h"
#include "MenuOutput.h"

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
MenuDisplay menu = MenuDisplay(&lcd);

void setup() {
  MenuTier *home = new MenuTier("Home");
  new MenuOutput("Check now", home);

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
  new MenuOutput("Test wireless", wireless);

  menu.enable(home);
}

void loop() {
  menu.render();
}

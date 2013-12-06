#include <Wire.h>

#include "Adafruit_MCP23017.h"
#include "Adafruit_RGBLCDShield.h"
#include "MenuDisplay.h"

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
MenuDisplay menu = MenuDisplay(lcd);

void setup() {
  MenuEntry *menuCheckNow = new MenuEntry("Check now");
  MenuEntry *menuSettings = new MenuEntry("Settings");
  menuCheckNow->setSibling(menuSettings);

  MenuEntry *menuSetName       = new MenuEntry("Name",          menuSettings);
  MenuEntry *menuSetThreshold  = new MenuEntry("Threshold",     menuSettings);
  MenuEntry *menuNotifications = new MenuEntry("Notifications", menuSettings);
  MenuEntry *menuWireless      = new MenuEntry("Wireless",      menuSettings);
  menuSettings->child = menuSetName;
  menuSetName->setSibling(menuSetThreshold);
  menuSetThreshold->setSibling(menuNotifications);
  menuNotifications->setSibling(menuWireless);

  MenuEntry *menuSetEmail        = new MenuEntry("E-mail",        menuNotifications);
  MenuEntry *menuSetPhone        = new MenuEntry("Phone number",  menuNotifications);
  MenuEntry *menuSetEarliestTime = new MenuEntry("Earliest time", menuNotifications);
  MenuEntry *menuSetLatestTime   = new MenuEntry("Latest time",   menuNotifications);
  menuNotifications->child = menuSetEmail;
  menuSetEmail->setSibling(menuSetPhone);
  menuSetPhone->setSibling(menuSetEarliestTime);
  menuSetEarliestTime->setSibling(menuSetLatestTime);

  MenuEntry *menuSetSSID     = new MenuEntry("SSID",     menuWireless);
  MenuEntry *menuSetUsername = new MenuEntry("Username", menuWireless);
  MenuEntry *menuSetPassword = new MenuEntry("Password", menuWireless);
  menuWireless->child = menuSetSSID;
  menuSetSSID->setSibling(menuSetUsername);
  menuSetUsername->setSibling(menuSetPassword);

  menu.enable(*menuCheckNow);
}

void loop() {
  menu.update();
}

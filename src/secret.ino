#include <Wire.h>

#include "Adafruit_MCP23017.h"
#include "Adafruit_RGBLCDShield.h"

#include "MenuDisplay.h"
#include "MenuEntry.h"
#include "MenuTier.h"

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
MenuDisplay menu = MenuDisplay(&lcd);

void setup() {
  MenuTier *menuHome = new MenuTier("Home");

  MenuEntry *menuCheckNow = new MenuEntry("Check now", menuHome);
  MenuTier  *menuSettings = new MenuTier ("Settings",  menuHome);

  MenuEntry *menuSetName       = new MenuEntry("Name",          menuSettings);
  MenuEntry *menuSetThreshold  = new MenuEntry("Threshold",     menuSettings);
  MenuTier  *menuNotifications = new MenuTier ("Notifications", menuSettings);
  MenuTier  *menuWireless      = new MenuTier ("Wireless",      menuSettings);

  MenuEntry *menuSetEmail        = new MenuEntry("E-mail",        menuNotifications);
  MenuEntry *menuSetPhone        = new MenuEntry("Phone number",  menuNotifications);
  MenuEntry *menuSetEarliestTime = new MenuEntry("Earliest time", menuNotifications);
  MenuEntry *menuSetLatestTime   = new MenuEntry("Latest time",   menuNotifications);

  MenuEntry *menuSetSSID      = new MenuEntry("SSID",          menuWireless);
  MenuEntry *menuSetUsername  = new MenuEntry("Username",      menuWireless);
  MenuEntry *menuSetPassword  = new MenuEntry("Password",      menuWireless);
  MenuEntry *menuTestWireless = new MenuEntry("Test wireless", menuWireless);

  menu.enable(menuHome);
}

void loop() {
  menu.render();
}

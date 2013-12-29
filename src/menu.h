#ifndef _Menu_
#define _Menu_

#include "menu/menu.h"

#include "notifier.h"
#include "sensor.h"

class Menu {
  public:
    static MenuEntry* home();

  private:
    static MenuEntry* homeChild(byte i);
    static __FlashStringHelper* homeChildName(byte i);

    static MenuEntry* settings();
    static MenuEntry* settingsChild(byte i);
    static __FlashStringHelper* settingsChildName(byte i);

    static MenuEntry* notifications();
    static MenuEntry* notificationsChild(byte i);
    static __FlashStringHelper* notificationsChildName(byte i);

    static MenuEntry* wireless();
    static MenuEntry* wirelessChild(byte i);
    static __FlashStringHelper* wirelessChildName(byte i);

    static void printMoistureLevel(Adafruit_RGBLCDShield *lcd);
    static void testWireless(Adafruit_RGBLCDShield *lcd);
};

#endif

#ifndef _MenuEntry_
#define _MenuEntry_

#include <Arduino.h>

#include "Adafruit_RGBLCDShield.h"

class MenuEntry {
  public:
    static boolean buttonPressed;
    static long buttonHeldAt;
    static byte buttonHoldInterval;

    static byte pressedButton(Adafruit_RGBLCDShield *lcd);
    static byte heldButton(Adafruit_RGBLCDShield *lcd);

    MenuEntry* (*getParent)();

    MenuEntry(MenuEntry* (*getParent)() = NULL);

    virtual MenuEntry* render(Adafruit_RGBLCDShield *lcd, boolean init = false) = 0;
};

#endif

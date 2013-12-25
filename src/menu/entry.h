#ifndef _MenuEntry_
#define _MenuEntry_

#include <Arduino.h>

#include "Adafruit_RGBLCDShield.h"

#define MENU_TIER   0x0
#define MENU_INPUT  0x1
#define MENU_OUTPUT 0x2

class MenuEntry {
  public:
    static boolean buttonPressed;
    static long buttonHeldAt;
    static byte buttonHoldInterval;

    static byte pressedButton(Adafruit_RGBLCDShield *lcd);
    static byte heldButton(Adafruit_RGBLCDShield *lcd);

    __FlashStringHelper *name;
    MenuEntry *nextSibling;
    MenuEntry *prevSibling;
    MenuEntry *parent;

    MenuEntry(__FlashStringHelper *name, MenuEntry *parent = NULL);

    virtual byte type() = 0;
    virtual MenuEntry* render(Adafruit_RGBLCDShield *lcd, boolean init = false) = 0;
};

#endif

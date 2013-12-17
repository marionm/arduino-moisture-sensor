#ifndef _MenuEntry_
#define _MenuEntry_

#include <Arduino.h>

#include "Adafruit_RGBLCDShield.h"

#define MENU_TIER   0x0
#define MENU_INPUT  0x1
#define MENU_OUTPUT 0x2

class MenuEntry {
  public:
    __FlashStringHelper *name;
    MenuEntry *nextSibling;
    MenuEntry *prevSibling;
    MenuEntry *parent;

    MenuEntry(__FlashStringHelper *name, MenuEntry *parent = NULL);

    virtual byte type() = 0;
    virtual MenuEntry* render(Adafruit_RGBLCDShield *lcd, boolean init = false) = 0;

  protected:
    boolean buttonPressed;
    long buttonHeldAt;
    byte buttonHoldInterval;

    byte pressedButton(Adafruit_RGBLCDShield *lcd);
    byte heldButton(Adafruit_RGBLCDShield *lcd);
};

#endif

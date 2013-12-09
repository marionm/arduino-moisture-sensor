#ifndef _MenuEntry_
#define _MenuEntry_

#include <Arduino.h>

#include "Adafruit_RGBLCDShield.h"

#define MENU_ENTRY 0x0
#define MENU_TIER  0x1

class MenuEntry {
  public:
    String name;
    MenuEntry *nextSibling;
    MenuEntry *prevSibling;

    // Actually a MenuTier, but need to avoid circular dependency
    MenuEntry *parent;

    MenuEntry(String name, MenuEntry *parent = NULL);

    virtual byte type();
    virtual MenuEntry* render(Adafruit_RGBLCDShield *lcd, boolean init = false);

  protected:
    byte pressedButton(Adafruit_RGBLCDShield *lcd);
    boolean buttonPressed;
};

#endif

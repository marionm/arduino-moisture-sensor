#ifndef _MenuTier_
#define _MenuTier_

#include "Adafruit_RGBLCDShield.h"
#include "entry.h"

class MenuTier :
public MenuEntry {
  public:
    MenuTier(
      byte                 childCount,
      MenuEntry*           (*getChild)(byte i),
      __FlashStringHelper* (*getChildName)(byte i),
      MenuEntry*           (*getParent)() = NULL
    );

    MenuEntry* render(Adafruit_RGBLCDShield *lcd, boolean init = false);

  private:
    byte childIndex;
    byte childCount;
    MenuEntry* (*getChild)(byte i);
    __FlashStringHelper* (*getChildName)(byte i);

    void renderScreen(Adafruit_RGBLCDShield *lcd);
};

#endif

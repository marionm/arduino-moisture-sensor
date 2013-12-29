#ifndef _MenuOutput_
#define _MenuOutput_

#include <Arduino.h>

#include "Adafruit_RGBLCDShield.h"
#include "entry.h"

class MenuOutput :
public MenuEntry {
  public:
    MenuOutput(__FlashStringHelper *name, MenuEntry* (*getParent)(), void (*printValue)(Adafruit_RGBLCDShield *lcd));

    MenuEntry* render(Adafruit_RGBLCDShield *lcd, boolean init = false);

  private:
    void (*printValue)(Adafruit_RGBLCDShield *lcd);
};

#endif

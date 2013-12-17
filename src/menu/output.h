#ifndef _MenuOutput_
#define _MenuOutput_

#include <Arduino.h>

#include "Adafruit_RGBLCDShield.h"
#include "entry.h"

class MenuOutput :
public MenuEntry {
  public:
    MenuOutput(__FlashStringHelper *name, MenuEntry *parent, String (*valueFunction)());

    byte type();
    MenuEntry* render(Adafruit_RGBLCDShield *lcd, boolean init = false);

  private:
    String value;
    String (*getValue)();
};

#endif

#ifndef _MenuOutput_
#define _MenuOutput_

#include "Adafruit_RGBLCDShield.h"
#include "MenuEntry.h"

class MenuOutput :
public MenuEntry {
  public:
    MenuOutput(String name, MenuEntry *parent = NULL);

    byte type();
    MenuEntry* render(Adafruit_RGBLCDShield *lcd, boolean init = false);
};

#endif

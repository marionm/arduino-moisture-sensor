#ifndef _MenuInput_
#define _MenuInput_

#include "Adafruit_RGBLCDShield.h"
#include "MenuEntry.h"

class MenuInput :
public MenuEntry {
  public:
    MenuInput(String name, MenuEntry *parent = NULL);

    byte type();
    MenuEntry* render(Adafruit_RGBLCDShield *lcd, boolean init = false);
};

#endif

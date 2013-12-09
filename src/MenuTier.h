#ifndef _MenuTier_
#define _MenuTier_

#include "Adafruit_RGBLCDShield.h"
#include "MenuEntry.h"

class MenuTier :
public MenuEntry {
  public:
    MenuTier(String name, MenuEntry *parent = NULL);

    byte type();
    MenuEntry* render(Adafruit_RGBLCDShield *lcd, boolean init = false);

    void addChild(MenuEntry *child);

  private:
    MenuEntry *headChild;
    MenuEntry *currentChild;

    void renderScreen(Adafruit_RGBLCDShield *lcd);
};

#endif

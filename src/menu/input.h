#ifndef _MenuInput_
#define _MenuInput_

#include <Arduino.h>

#include "Adafruit_RGBLCDShield.h"
#include "entry.h"
#include "settings.h"

class MenuInput :
public MenuEntry {
  public:
    MenuInput(__FlashStringHelper *name, MenuEntry *parent, byte settingIndex);

    byte type();
    MenuEntry* render(Adafruit_RGBLCDShield *lcd, boolean init = false);

  protected:
    char storedValue[MENU_STORAGE_SIZE];

    virtual void setupLcd(Adafruit_RGBLCDShield *lcd);
    virtual void teardownLcd(Adafruit_RGBLCDShield *lcd);
    virtual void handleInput(Adafruit_RGBLCDShield *lcd, byte pressedButton, byte heldButton) = 0;

  private:
    byte settingIndex;
};

#endif

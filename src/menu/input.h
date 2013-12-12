#ifndef _MenuInput_
#define _MenuInput_

#include <Arduino.h>

#include "Adafruit_RGBLCDShield.h"
#include "entry.h"
#include "settings.h"

class MenuInput :
public MenuEntry {
  public:
    MenuInput(String name, MenuEntry *parent, MenuSettings *settings);

    byte type();
    MenuEntry* render(Adafruit_RGBLCDShield *lcd, boolean init = false);

  private:
    static String characters;

    MenuSettings *settings;
    byte editIndex;
    byte characterIndex;
    String storedValue;

    inline void writeCharacter(Adafruit_RGBLCDShield *lcd, byte index, char character);
};

#endif

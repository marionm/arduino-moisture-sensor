#ifndef _MenuInput_
#define _MenuInput_

#include <Arduino.h>

#include "Adafruit_RGBLCDShield.h"
#include "entry.h"

class MenuInput :
public MenuEntry {
  public:
    MenuInput(String name, MenuEntry *parent);

    byte type();
    MenuEntry* render(Adafruit_RGBLCDShield *lcd, boolean init = false);

  private:
    static String characters;

    byte editIndex;
    byte characterIndex;
    String storedValue;

    String readStorage();
    void writeStorage(String value);

    inline void writeCharacter(Adafruit_RGBLCDShield *lcd, byte index, char character);
};

#endif

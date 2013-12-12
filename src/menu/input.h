#ifndef _MenuInput_
#define _MenuInput_

#include <Arduino.h>

#include "Adafruit_RGBLCDShield.h"
#include "entry.h"
#include "settings.h"

class MenuInput :
public MenuEntry {
  public:
    struct CharacterSets {
      static String numeric;
      static String lettersOnly;
      static String letters;
      static String alphanumeric;
      static String email;
      static String full;
    };

    MenuInput(String name, MenuEntry *parent, MenuSettings *settings, String *characterSet = &MenuInput::CharacterSets::alphanumeric);

    byte type();
    MenuEntry* render(Adafruit_RGBLCDShield *lcd, boolean init = false);

  private:
    String *characterSet;
    MenuSettings *settings;
    byte editIndex;
    byte characterIndex;
    String storedValue;

    inline void writeCharacter(Adafruit_RGBLCDShield *lcd, byte index, char character);
};

#endif

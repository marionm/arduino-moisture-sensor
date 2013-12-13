#ifndef _TextMenuInput_
#define _TextMenuInput_

#include <Arduino.h>

#include "input.h"

class TextMenuInput :
public MenuInput {
  public:
    struct CharacterSets {
      static String numeric;
      static String alphanumeric;
      static String email;
      static String full;
    };

    TextMenuInput(
      String name, MenuEntry *parent, MenuSettings *settings,
      String characterSet = TextMenuInput::CharacterSets::alphanumeric
    );

  protected:
    void setupLcd(Adafruit_RGBLCDShield *lcd);
    void teardownLcd(Adafruit_RGBLCDShield *lcd);
    void handleInput(Adafruit_RGBLCDShield *lcd, byte button);

  private:
    String *characterSet;
    byte characterIndex;
    byte editIndex;
};

#endif

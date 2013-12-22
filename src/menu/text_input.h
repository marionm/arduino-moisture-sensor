#ifndef _TextMenuInput_
#define _TextMenuInput_

#include <Arduino.h>

#include "input.h"

#define NUMERIC_CHARACTER_SET      0
#define ALPHANUMERIC_CHARACTER_SET 1
#define EMAIL_CHARACTER_SET        2
#define FULL_CHARACTER_SET         3

class TextMenuInput :
public MenuInput {
  public:
    TextMenuInput(
      __FlashStringHelper *name, MenuEntry *parent, byte settingsIndex,
      byte characterSet = ALPHANUMERIC_CHARACTER_SET
    );

  protected:
    void setupLcd(Adafruit_RGBLCDShield *lcd);
    void teardownLcd(Adafruit_RGBLCDShield *lcd);
    void handleInput(Adafruit_RGBLCDShield *lcd, byte pressedButton, byte heldButton);

  private:
    byte characterSet;
    byte editIndex;
    char currentCharacter;

    char nextCharacter(char character);
    char prevCharacter(char character);
    char defaultCharacter();
    void writeCharacter(Adafruit_RGBLCDShield *lcd, byte index, char character);
};

#endif

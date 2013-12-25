#include "numeric_input.h"
#include "util.h"

NumericMenuInput::NumericMenuInput(__FlashStringHelper *name, MenuEntry* (*getParent)(), byte settingsIndex, byte _min, byte _max) :
MenuInput(name, getParent, settingsIndex) {
  min = _min;
  max = _max;

  if(strcmp(storedValue, "") == 0 || strcmp(storedValue, " ") == 0) {
    strcpy(storedValue, MenuUtil::byteToString(min));
  }
}

void NumericMenuInput::handleInput(Adafruit_RGBLCDShield *lcd, byte pressedButton, byte heldButton) {
  if(heldButton & (BUTTON_UP | BUTTON_DOWN)) {
    byte numericValue = MenuUtil::stringToByte(storedValue);

    if(heldButton & BUTTON_UP) {
      if(numericValue == max) {
        numericValue = min;
      } else {
        numericValue++;
      }
    }

    if(heldButton & BUTTON_DOWN) {
      if(numericValue == 0) {
        numericValue = max;
      } else {
        numericValue--;
      }
    }

    strcpy(storedValue, MenuUtil::byteToString(numericValue));

    lcd->setCursor(0, 1);
    for(byte i = 0; i < (max / 10 + 1); i++) {
      lcd->print(" ");
    }
    lcd->setCursor(0, 1);
    lcd->print(storedValue);
  }
}

#include "numeric_input.h"

NumericMenuInput::NumericMenuInput(String name, MenuEntry *parent, byte settingsIndex, byte _min, byte _max) :
MenuInput(name, parent, settingsIndex) {
  min = _min;
  max = _max;

  if(storedValue == "" || storedValue == " ") {
    numericValue = 0;
    storedValue = "0";
  } else {
    numericValue = storedValue.toInt();
  }
}

void NumericMenuInput::handleInput(Adafruit_RGBLCDShield *lcd, byte pressedButton, byte heldButton) {
  boolean change = false;

  if(heldButton & BUTTON_UP) {
    if(numericValue == max) {
      numericValue = min;
    } else {
      numericValue++;
    }
    change = true;
  }

  if(heldButton & BUTTON_DOWN) {
    if(numericValue == 0) {
      numericValue = max;
    } else {
      numericValue--;
    }
    change = true;
  }

  if(change) {
    lcd->setCursor(0, 1);
    for(byte i = 0; i < String(max).length(); i++) {
      lcd->print(" ");
    }
    lcd->setCursor(0, 1);
    lcd->print(numericValue);
    storedValue = String(numericValue);
  }
}

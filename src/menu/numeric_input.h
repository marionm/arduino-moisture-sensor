#ifndef _NumericMenuInput_
#define _NumericMenuInput_

#include <Arduino.h>

#include "input.h"

class NumericMenuInput:
public MenuInput {
  public:
    NumericMenuInput(__FlashStringHelper *name, MenuEntry *parent, byte settingsIndex, byte min = 0, byte max = 100);

  protected:
    void handleInput(Adafruit_RGBLCDShield *lcd, byte pressedButton, byte heldButton);

  private:
    byte numericValue;
    byte min;
    byte max;
};

#endif

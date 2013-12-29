#include "output.h"

MenuOutput::MenuOutput(__FlashStringHelper *name, MenuEntry* (*getParent)(), void (*_printValue)(Adafruit_RGBLCDShield *lcd)) :
MenuEntry(getParent) {
  printValue = _printValue;
}

MenuEntry* MenuOutput::render(Adafruit_RGBLCDShield *lcd, boolean init) {
  byte button = pressedButton(lcd);

  if(button & BUTTON_SELECT || init) {
    printValue(lcd);
  } else if(button & BUTTON_LEFT) {
    return getParent();
  }

  return this;
}

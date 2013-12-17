#include "output.h"

MenuOutput::MenuOutput(__FlashStringHelper *name, MenuEntry *parent, void (*_getAndPrintValue)(Adafruit_RGBLCDShield *lcd)) :
MenuEntry(name, parent) {
  getAndPrintValue = _getAndPrintValue;
}

byte MenuOutput::type() {
  return MENU_OUTPUT;
}

MenuEntry* MenuOutput::render(Adafruit_RGBLCDShield *lcd, boolean init) {
  byte button = pressedButton(lcd);

  if(button & BUTTON_SELECT || init) {
    getAndPrintValue(lcd);
  } else if(button & BUTTON_LEFT && parent) {
    return parent;
  }

  return this;
}

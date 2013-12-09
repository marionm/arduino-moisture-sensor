#include "output.h"

MenuOutput::MenuOutput(String name, MenuEntry *parent, String (*valueFunction)()) :
MenuEntry(name, parent) {
  value    = NULL;
  getValue = valueFunction;
}

byte MenuOutput::type() {
  return MENU_OUTPUT;
}

MenuEntry* MenuOutput::render(Adafruit_RGBLCDShield *lcd, boolean init) {
  byte button = pressedButton(lcd);

  if(button & BUTTON_SELECT || init) {
    value = getValue();
    lcd->clear();
    lcd->print(value);
  } else if(button & BUTTON_LEFT && parent) {
    return parent;
  }

  return this;
}

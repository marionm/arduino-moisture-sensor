#include "MenuOutput.h"

MenuOutput::MenuOutput(String name, MenuEntry *parent) :
MenuEntry(name, parent) {
}

byte MenuOutput::type() {
  return MENU_OUTPUT;
}

MenuEntry* MenuOutput::render(Adafruit_RGBLCDShield *lcd, boolean init) {
  if(init) {
    lcd->clear();
    lcd->print(name);
  }

  byte button = pressedButton(lcd);
  if(button & BUTTON_LEFT && parent) {
    return parent;
  }

  return this;
}

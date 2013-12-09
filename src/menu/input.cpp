#include "input.h"

MenuInput::MenuInput(String name, MenuEntry *parent) :
MenuEntry(name, parent) {
}

byte MenuInput::type() {
  return MENU_INPUT;
}

MenuEntry* MenuInput::render(Adafruit_RGBLCDShield *lcd, boolean init) {
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

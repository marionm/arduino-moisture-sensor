#include "MenuEntry.h"
#include "MenuTier.h"

MenuEntry::MenuEntry(String _name, MenuEntry *_parent) {
  name        = _name;
  parent      = _parent;
  nextSibling = NULL;
  prevSibling = NULL;

  buttonPressed = false;

  if(parent && parent->type() == MENU_TIER) {
    ((MenuTier*)parent)->addChild(this);
  }
}

byte MenuEntry::type() {
  return MENU_ENTRY;
}

MenuEntry* MenuEntry::render(Adafruit_RGBLCDShield *lcd, boolean init) {
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

byte MenuEntry::pressedButton(Adafruit_RGBLCDShield *lcd) {
  byte button = lcd->readButtons();
  if(button && !buttonPressed) {
    buttonPressed = true;
    return button;
  } else if(!button){
    buttonPressed = false;
  }
  return NULL;
}

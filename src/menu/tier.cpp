#include "tier.h"

MenuTier::MenuTier(
  byte                 _childCount,
  MenuEntry*           (*_getChild)(byte i),
  __FlashStringHelper* (*_getChildName)(byte i),
  MenuEntry*           (*getParent)()
) : MenuEntry(getParent) {
  childCount   = _childCount;
  getChild     = _getChild;
  getChildName = _getChildName;

  childIndex = 0;
}

MenuEntry* MenuTier::render(Adafruit_RGBLCDShield *lcd, boolean init) {
  MenuEntry* nextEntry = this;

  if(init) {
    renderScreen(lcd);
    return nextEntry;
  }

  byte button = pressedButton(lcd); 
  if(button & BUTTON_UP) {
    if(childIndex == 0) {
      childIndex = childCount - 1;
    } else {
      childIndex--;
    }
    renderScreen(lcd);

  } else if(button & BUTTON_DOWN) {
    childIndex++;
    if(childIndex >= childCount) {
      childIndex = 0;
    }
    renderScreen(lcd);

  } else if(button & BUTTON_LEFT) {
    MenuEntry *parent = getParent();
    if(parent) {
      nextEntry = parent;
    }

  } else if(button & (BUTTON_RIGHT | BUTTON_SELECT)) {
    nextEntry = getChild(childIndex);
  }

  return nextEntry;
}

void MenuTier::renderScreen(Adafruit_RGBLCDShield *lcd) {
  lcd->clear();

  byte row = childIndex % 2;
  lcd->setCursor(0, row);
  lcd->print(">");

  byte index = childIndex - row;
  lcd->setCursor(2, 0);
  lcd->print(getChildName(index));

  index++;
  if(index < childCount) {
    lcd->setCursor(2, 1);
    lcd->print(getChildName(index));
  }
}

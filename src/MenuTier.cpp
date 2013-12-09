#include "MenuTier.h"

MenuTier::MenuTier(String name, MenuEntry *parent) :
MenuEntry(name, parent) {
  headChild    = NULL;
  currentChild = NULL;
}

byte MenuTier::type() {
  return MENU_TIER;
}

void MenuTier::addChild(MenuEntry *child) {
  if(headChild) {
    MenuEntry *tail = headChild;
    while(tail->nextSibling) {
      tail = tail->nextSibling;
    }
    tail->nextSibling = child;
    child->prevSibling = tail;
  } else {
    headChild = child;
    currentChild = child;
  }
}

MenuEntry* MenuTier::render(Adafruit_RGBLCDShield *lcd, boolean init) {
  MenuEntry* nextEntry = this;

  if(init) {
    renderScreen(lcd);
    return nextEntry;
  }

  byte button = pressedButton(lcd); 
  if(button & BUTTON_UP) {
    if(currentChild->prevSibling) {
      currentChild = currentChild->prevSibling;
    } else {
      currentChild = headChild;
      while(currentChild->nextSibling) {
        currentChild = currentChild->nextSibling;
      }
    }
    renderScreen(lcd);

  } else if(button & BUTTON_DOWN) {
    if(currentChild->nextSibling) {
      currentChild = currentChild->nextSibling;
    } else {
      currentChild = headChild;
    }
    renderScreen(lcd);

  } else if(button & BUTTON_LEFT && parent) {
    currentChild = headChild;
    nextEntry = parent;

  } else if(button & (BUTTON_RIGHT | BUTTON_SELECT)) {
    nextEntry = currentChild;
  }

  return nextEntry;
}

void MenuTier::renderScreen(Adafruit_RGBLCDShield *lcd) {
  lcd->clear();
  if(!currentChild) return;

  byte row = 0;
  MenuEntry *child = headChild;
  while(child != currentChild) {
    child = child->nextSibling;
    row += 1;
  }
  row %= 2;

  lcd->setCursor(0, row);
  lcd->print(">");

  if(row != 0) {
    child = currentChild->prevSibling;
  }
  lcd->setCursor(2, 0);
  lcd->print(child->name);

  child = child->nextSibling;
  if(child) {
    lcd->setCursor(2, 1);
    lcd->print(child->name);
  }
}

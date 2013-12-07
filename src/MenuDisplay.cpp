#include "MenuDisplay.h"

MenuDisplay::MenuDisplay(Adafruit_RGBLCDShield *_lcd) {
  lcd = _lcd;
  buttonPressed = false;
}

void MenuDisplay::enable(MenuEntry *entry) {
  lcd->begin(16, 2);

  currentEntry = entry;
  renderScreen();
}

void MenuDisplay::disable() {
  // Turn off LCD
}

void MenuDisplay::update() {
  byte buttons = lcd->readButtons();
  if(buttons && !buttonPressed) {
    buttonPressed = true;
    update(buttons, currentEntry);
  } else if(!buttons) {
    buttonPressed = false;
  }
}

void MenuDisplay::update(byte buttons, MenuEntry *entry) {
  if(buttons & BUTTON_UP) {
    if(currentEntry->prevSibling) {
      currentEntry = currentEntry->prevSibling;
    } else {
      while(currentEntry->nextSibling) {
        currentEntry = currentEntry->nextSibling;
      }
    }
    renderScreen();

  } else if(buttons & BUTTON_DOWN) {
    if(currentEntry->nextSibling) {
      currentEntry = currentEntry->nextSibling;
    } else {
      while(currentEntry->prevSibling) {
        currentEntry = currentEntry->prevSibling;
      }
    }
    renderScreen();

  } else if(buttons & BUTTON_LEFT && currentEntry->parent) {
    currentEntry = currentEntry->parent;
    renderScreen();

  } else if(buttons & (BUTTON_RIGHT | BUTTON_SELECT) && currentEntry->child) {
    currentEntry = currentEntry->child;
    renderScreen();
  }
}

void MenuDisplay::renderScreen() {
  lcd->clear();

  lcd->setCursor(0, 0);
  lcd->print("> ");
  lcd->print(currentEntry->name);

  if(currentEntry->nextSibling) {
    lcd->setCursor(0, 1);
    lcd->print("  ");
    lcd->print(currentEntry->nextSibling->name);
  }
}

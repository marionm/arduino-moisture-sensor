#include "MenuDisplay.h"

MenuDisplay::MenuDisplay(Adafruit_RGBLCDShield *_lcd) {
  lcd = _lcd;
}

void MenuDisplay::enable(MenuEntry *entry) {
  lcd->begin(16, 2);
  currentEntry = entry;
  currentEntry->render(lcd, true);
}

void MenuDisplay::disable() {
  // TODO: Turn off LCD
}

void MenuDisplay::render() {
  MenuEntry *next = currentEntry->render(lcd);
  if(next != currentEntry) {
    next->render(lcd, true);
    currentEntry = next;
  }
}

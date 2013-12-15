#include "input.h"

MenuInput::MenuInput(String name, MenuEntry *parent, byte _settingIndex) :
MenuEntry(name, parent) {
  settingIndex = _settingIndex;
  storedValue  = MenuSettings::getValue(settingIndex);
}

byte MenuInput::type() {
  return MENU_INPUT;
}

void MenuInput::setupLcd(Adafruit_RGBLCDShield *lcd) {
  // noop
}

void MenuInput::teardownLcd(Adafruit_RGBLCDShield *lcd) {
  // noop
}

MenuEntry* MenuInput::render(Adafruit_RGBLCDShield *lcd, boolean init) {
  if(init) {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print(name);

    lcd->setCursor(0, 1);
    lcd->print(storedValue);

    setupLcd(lcd);
  }

  byte button = pressedButton(lcd);
  if(button & BUTTON_SELECT) {
    teardownLcd(lcd);
    MenuSettings::setValue(settingIndex, storedValue);
    return parent;
  }

  handleInput(lcd, button, heldButton(lcd));

  return this;
}

void MenuInput::writeCharacter(Adafruit_RGBLCDShield *lcd, byte index, char character) {
  lcd->setCursor(index, 1);
  lcd->print(character);
  lcd->setCursor(index, 1);
}

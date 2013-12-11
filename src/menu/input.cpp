#include "input.h"

String MenuInput::characters = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*?/\\,.-_=+()[]{}<>\|;:~`'\"";

MenuInput::MenuInput(String name, MenuEntry *parent) :
MenuEntry(name, parent) {
  storedValue = " ";
  editIndex = storedValue.length() - 1;
  characterIndex = characters.indexOf(storedValue[storedValue.length() - 1]);
}

byte MenuInput::type() {
  return MENU_INPUT;
}

MenuEntry* MenuInput::render(Adafruit_RGBLCDShield *lcd, boolean init) {
  if(init) {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print(name);

    lcd->setCursor(0, 1);
    lcd->print(storedValue);

    lcd->setCursor(editIndex, 1);
    lcd->cursor();
  }

  byte button = pressedButton(lcd);
  if(button & BUTTON_SELECT) {
    lcd->noCursor();
    writeStorage(storedValue);
    return parent;
  }

  if(button & BUTTON_LEFT && editIndex > 0) {
    storedValue = storedValue.substring(0, storedValue.length() - 1);
    lcd->setCursor(editIndex, 1);
    editIndex -= 1;
    lcd->print(" ");
    lcd->setCursor(editIndex, 1);
  }

  if(button & BUTTON_RIGHT && editIndex < 15) {
    char character = characters[characterIndex];
    storedValue = storedValue += character;
    editIndex += 1;
    writeCharacter(lcd, editIndex, character);
  }

  if(button & BUTTON_UP | BUTTON_DOWN) {
    if(button & BUTTON_UP) {
      characterIndex += 1;
      if(characterIndex >= characters.length()) {
        characterIndex = 0;
      }
    }

    if(button & BUTTON_DOWN) {
      if(characterIndex == 0) {
        characterIndex = characters.length();
      }
      characterIndex -= 1;
    }

    char character = characters[characterIndex];
    storedValue.setCharAt(storedValue.length() - 1, character);
    writeCharacter(lcd, editIndex, character);
  }

  return this;
}

String MenuInput::readStorage() {
  // TODO
  return "";
}

void MenuInput::writeStorage(String value) {
  // TODO
}

inline void MenuInput::writeCharacter(Adafruit_RGBLCDShield *lcd, byte index, char character) {
  lcd->setCursor(index, 1);
  lcd->print(character);
  lcd->setCursor(index, 1);
}

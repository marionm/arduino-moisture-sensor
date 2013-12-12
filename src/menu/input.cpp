#include "input.h"

String MenuInput::CharacterSets::numeric      = "012345679";
String MenuInput::CharacterSets::letters      = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
String MenuInput::CharacterSets::alphanumeric = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
String MenuInput::CharacterSets::email        = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-+.@";
String MenuInput::CharacterSets::full         = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-+.@,!#$%^&*?/\\=()[]{}<>\|;:~`'\" ";

MenuInput::MenuInput(String name, MenuEntry *parent, MenuSettings *_settings, String *_characterSet) :
MenuEntry(name, parent) {
  settings    = _settings;
  storedValue = settings->getValue();
  editIndex   = storedValue.length() - 1;

  characterSet   = _characterSet;
  characterIndex = characterSet->indexOf(storedValue[storedValue.length() - 1]);
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
    settings->setValue(storedValue);
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
    char character = characterSet->charAt(characterIndex);
    storedValue = storedValue += character;
    editIndex += 1;
    writeCharacter(lcd, editIndex, character);
  }

  if(button & BUTTON_UP | BUTTON_DOWN) {
    if(button & BUTTON_UP) {
      characterIndex += 1;
      if(characterIndex >= characterSet->length()) {
        characterIndex = 0;
      }
    }

    if(button & BUTTON_DOWN) {
      if(characterIndex == 0) {
        characterIndex = characterSet->length();
      }
      characterIndex -= 1;
    }

    char character = characterSet->charAt(characterIndex);
    storedValue.setCharAt(storedValue.length() - 1, character);
    writeCharacter(lcd, editIndex, character);
  }

  return this;
}

inline void MenuInput::writeCharacter(Adafruit_RGBLCDShield *lcd, byte index, char character) {
  lcd->setCursor(index, 1);
  lcd->print(character);
  lcd->setCursor(index, 1);
}

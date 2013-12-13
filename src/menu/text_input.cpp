#include "text_input.h"

String TextMenuInput::CharacterSets::numeric      = "0123456789";
String TextMenuInput::CharacterSets::alphanumeric = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
String TextMenuInput::CharacterSets::email        = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-+.@";
String TextMenuInput::CharacterSets::full         = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-+.@,!#$%^&*?/\\=()[]{}<>\|;:~`'\" ";

TextMenuInput::TextMenuInput(String name, MenuEntry *parent, MenuSettings *settings, String _characterSet) :
MenuInput(name, parent, settings) {
  editIndex      = storedValue.length() - 1;
  characterSet   = &_characterSet;
  characterIndex = characterSet->indexOf(storedValue[storedValue.length() - 1]);
  if(characterIndex == -1) {
    characterIndex = 0;
  }
}

void TextMenuInput::setupLcd(Adafruit_RGBLCDShield *lcd) {
  lcd->cursor();
  lcd->setCursor(editIndex, 1);
}

void TextMenuInput::teardownLcd(Adafruit_RGBLCDShield *lcd) {
  lcd->noCursor();
}

void TextMenuInput::handleInput(Adafruit_RGBLCDShield *lcd, byte button) {
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
}

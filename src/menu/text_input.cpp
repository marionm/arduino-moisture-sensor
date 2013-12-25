#include "text_input.h"

TextMenuInput::TextMenuInput(__FlashStringHelper *name, MenuEntry* (*getParent)(), byte settingsIndex, byte _characterSet) :
MenuInput(name, getParent, settingsIndex) {
  characterSet = _characterSet;

  if(storedValue == "" || storedValue == " ") {
    storedValue[0] = defaultCharacter();
    storedValue[1] = '\0';
  }

  editIndex = strlen(storedValue) - 1;
  currentCharacter = storedValue[editIndex];
}

void TextMenuInput::setupLcd(Adafruit_RGBLCDShield *lcd) {
  lcd->cursor();
  lcd->setCursor(editIndex, 1);
}

void TextMenuInput::teardownLcd(Adafruit_RGBLCDShield *lcd) {
  lcd->noCursor();
}

void TextMenuInput::handleInput(Adafruit_RGBLCDShield *lcd, byte pressedButton, byte heldButton) {
  if(pressedButton & BUTTON_LEFT && editIndex > 0) {
    lcd->setCursor(editIndex, 1);
    lcd->print(" ");
    storedValue[editIndex] = '\0';

    editIndex -= 1;
    currentCharacter = storedValue[editIndex];
    lcd->setCursor(editIndex, 1);
  }

  if(pressedButton & BUTTON_RIGHT && editIndex < 15) {
    editIndex += 1;
    storedValue[editIndex] = currentCharacter;
    storedValue[editIndex + 1] = '\0';
    writeCharacter(lcd, editIndex, currentCharacter);
  }

  if(heldButton & BUTTON_UP | BUTTON_DOWN) {
    if(heldButton & BUTTON_UP) {
      currentCharacter = nextCharacter(currentCharacter);
    }
    if(heldButton & BUTTON_DOWN) {
      currentCharacter = prevCharacter(currentCharacter);
    }
    storedValue[editIndex] = currentCharacter;
    writeCharacter(lcd, editIndex, currentCharacter);
  }
}

char TextMenuInput::nextCharacter(char c) {
  if(characterSet == NUMERIC_CHARACTER_SET) {
    switch(c) {
      case '9': return '0';
    }
  } else if(characterSet == ALPHANUMERIC_CHARACTER_SET) {
    switch(c) {
      case 'Z': return 'a';
      case 'z': return '0';
      case '9': return ' ';
      case ' ': return 'A';
    }
  } else if(characterSet == EMAIL_CHARACTER_SET) {
    switch(c) {
      case 'z': return '0';
      case '9': return '_';
      case '_': return '-';
      case '-': return '+';
      case '+': return '.';
      case '.': return '@';
      case '@': return 'a';
    }
  } else if(characterSet == FULL_CHARACTER_SET) {
    switch(c) {
      case 'Z': return 'a';
      case 'z': return '0';
      case '9': return '!';
      case '/': return ':';
      case '@': return '[';
      case '`': return '{';
      case '~': return ' ';
      case ' ': return 'A';
    }
  }
  return c + 1;
}

char TextMenuInput::prevCharacter(char c) {
  if(characterSet == NUMERIC_CHARACTER_SET) {
    switch(c) {
      case '0': return '9';
    }
  } else if(characterSet == ALPHANUMERIC_CHARACTER_SET) {
    switch(c) {
      case 'A': return ' ';
      case ' ': return '9';
      case '0': return 'z';
      case 'a': return 'Z';
    }
  } else if(characterSet == EMAIL_CHARACTER_SET) {
    switch(c) {
      case 'a': return '@';
      case '@': return '.';
      case '.': return '+';
      case '+': return '-';
      case '-': return '_';
      case '_': return '9';
      case '0': return 'z';
    }
  } else if(characterSet == FULL_CHARACTER_SET) {
    switch(c) {
      case 'A': return ' ';
      case ' ': return '~';
      case '{': return '`';
      case '[': return '@';
      case ':': return '/';
      case '!': return '9';
      case '0': return 'z';
      case 'a': return 'Z';
    }
  }
  return c - 1;
}

char TextMenuInput::defaultCharacter() {
  if(characterSet == NUMERIC_CHARACTER_SET) {
    return '0';
  } else if(characterSet == EMAIL_CHARACTER_SET) {
    return 'a';
  } else {
    return ' ';
  }
}

void TextMenuInput::writeCharacter(Adafruit_RGBLCDShield *lcd, byte index, char character) {
  lcd->setCursor(index, 1);
  lcd->print(character);
  lcd->setCursor(index, 1);
}

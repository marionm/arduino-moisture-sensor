#include "text_input.h"

TextMenuInput::TextMenuInput(String name, MenuEntry *parent, MenuSettings *settings, byte _characterSet) :
MenuInput(name, parent, settings) {
  characterSet = _characterSet;

  if(storedValue == "" || storedValue == " ") {
    storedValue = String(defaultCharacter());
  }

  editIndex = storedValue.length() - 1;
  currentCharacter = storedValue.charAt(storedValue.length() - 1);
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
    storedValue = storedValue.substring(0, storedValue.length() - 1);
    currentCharacter = storedValue.charAt(storedValue.length() - 1);
    lcd->setCursor(editIndex, 1);
    lcd->print(" ");
    editIndex -= 1;
    lcd->setCursor(editIndex, 1);
  }

  if(pressedButton & BUTTON_RIGHT && editIndex < 15) {
    storedValue = storedValue + currentCharacter;
    editIndex += 1;
    writeCharacter(lcd, editIndex, currentCharacter);
  }

  if(heldButton & BUTTON_UP | BUTTON_DOWN) {
    if(heldButton & BUTTON_UP) {
      currentCharacter = nextCharacter(currentCharacter);
    }
    if(heldButton & BUTTON_DOWN) {
      currentCharacter = prevCharacter(currentCharacter);
    }
    storedValue.setCharAt(storedValue.length() - 1, currentCharacter);
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

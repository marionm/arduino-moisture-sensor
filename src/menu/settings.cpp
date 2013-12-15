#include <EEPROM.h>

#include "settings.h"

String MenuSettings::getValue(byte blockIndex) {
  byte index = memoryIndex(blockIndex);

  String value;

  char character = 255;
  byte i = 0;
  for(; i < MENU_STORAGE_SIZE; i++) {
    character = EEPROM.read(index + i);
    if(character < 32 || character > 126) {
      break;
    }
    value += character;
  }

  if(character != 0) {
    // No end of line character, not a real value
    return "";
  } else {
    return value;
  }
}

void MenuSettings::setValue(byte blockIndex, String value) {
  byte index = memoryIndex(blockIndex);

  if(value == getValue(blockIndex)) return;

  byte i = 0;
  for(; i < MENU_STORAGE_SIZE - 1 && i < value.length(); i++) {
    EEPROM.write(index + i, value[i]);
  }
  EEPROM.write(index + i, 0);
}

byte MenuSettings::memoryIndex(byte blockIndex) {
  return blockIndex * MENU_STORAGE_SIZE + MENU_STORAGE_START;
}

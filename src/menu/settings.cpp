#include <EEPROM.h>

#include "settings.h"

char *MenuSettings::getValue(byte blockIndex, boolean log) {
  byte index = memoryIndex(blockIndex);

  char value[17];

  char character = 255;
  byte i = 0;
  for(; i < MENU_STORAGE_SIZE; i++) {
    character = EEPROM.read(index + i);
    if(character < 32 || character > 126) {
      break;
    }
    value[i] = character;
  }

  value[i] = '\0';
  return value;
}

void MenuSettings::setValue(byte blockIndex, char *value) {
  if(strcmp(value, getValue(blockIndex, false)) == 0) return;

  byte index = memoryIndex(blockIndex);
  byte i = 0;
  for(; i < MENU_STORAGE_SIZE - 1 && i < strlen(value); i++) {
    EEPROM.write(index + i, value[i]);
  }
  EEPROM.write(index + i, 0);
}

byte MenuSettings::memoryIndex(byte blockIndex) {
  return blockIndex * MENU_STORAGE_SIZE + MENU_STORAGE_START;
}

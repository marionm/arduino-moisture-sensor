#include <EEPROM.h>

#include "eeprom_settings.h"

EEPROMMenuSettings::EEPROMMenuSettings(byte blockIndex) {
  memoryIndex = blockIndex * MENU_STORAGE_SIZE + MENU_STORAGE_START;
}

String EEPROMMenuSettings::getValue() {
  String value;

  char character = 255;
  byte i = 0;
  for(; i < MENU_STORAGE_SIZE; i++) {
    character = EEPROM.read(memoryIndex + i);
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

void EEPROMMenuSettings::setValue(String value) {
  if(value == getValue()) return;

  byte i = 0;
  for(; i < MENU_STORAGE_SIZE - 1 && i < value.length(); i++) {
    EEPROM.write(memoryIndex + i, value[i]);
  }
  EEPROM.write(memoryIndex + i, 0);
}

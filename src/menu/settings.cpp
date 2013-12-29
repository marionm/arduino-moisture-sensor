#include <EEPROM.h>

#include "settings.h"

char *MenuSettings::getValue(byte blockIndex, boolean log) {
  byte index = memoryIndex(blockIndex);

  char value[MENU_STORAGE_SIZE];

#ifdef _MenuSettingsDebug_
  if(log) {
    Serial.print(F("Starting read from "));
    Serial.println(blockIndex);
  }
#endif

  char character = 255;
  byte i = 0;
  for(; i < MENU_STORAGE_SIZE; i++) {
    character = EEPROM.read(index + i);

#ifdef _MenuSettingsDebug_
    if(log) Serial.print(F("  Read ")); Serial.print(character); Serial.print(" from index "); Serial.println(index + i);
#endif

    if(character < 32 || character > 126) {

#ifdef _MenuSettingsDebug_
      if(log) Serial.println(F("    Breaking"));
#endif

      break;
    }

#ifdef _MenuSettingsDebug_
    if(log) Serial.print(F("    Setting index ")); Serial.println(i);
#endif

    value[i] = character;
  }

  value[i] = '\0';

#ifdef _MenuSettingsDebug_
  if(log) {
    Serial.print(F("  Setting null terminator at index ")); Serial.println(i);
    Serial.print(F("  Returning "));
  }
#endif
  if(log) Serial.println(value);

  return value;
}

void MenuSettings::setValue(byte blockIndex, char *value) {
#ifdef _MenuSettingsDebug_
  Serial.print(F("Starting write of " )); Serial.print(value); Serial.print(F(" to index ")); Serial.println(blockIndex);
#endif
  if(strcmp(value, getValue(blockIndex, false)) == 0) {
#ifdef _MenuSettingsDebug_
    Serial.println(F("  Same as current value, returning"));
#endif
    return;
  }

  byte index = memoryIndex(blockIndex);
  byte i = 0;
  for(; i < MENU_STORAGE_SIZE - 1 && i < strlen(value); i++) {
#ifdef _MenuSettingsDebug_
    Serial.print(F("  Writing ")); Serial.print(value[i]); Serial.print(F(" to ")); Serial.println(index + i);
#endif
    EEPROM.write(index + i, value[i]);
  }
#ifdef _MenuSettingsDebug_
  Serial.print(F("  Finishing by writing 0 to ")); Serial.println(index + i);
#endif
  EEPROM.write(index + i, 0);
}

byte MenuSettings::memoryIndex(byte blockIndex) {
  return blockIndex * MENU_STORAGE_SIZE + MENU_STORAGE_START;
}

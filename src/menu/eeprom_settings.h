#ifndef _EEPROMMenuSettings_
#define _EEPROMMenuSettings_

#include <Arduino.h>

#include "settings.h"

#define MENU_STORAGE_START 0
#define MENU_STORAGE_SIZE 17

class EEPROMMenuSettings :
public MenuSettings {
  public:
    EEPROMMenuSettings(byte blockIndex);

    String getValue();
    void setValue(String value);

  private:
    byte memoryIndex;
};

#endif

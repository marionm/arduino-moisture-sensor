#ifndef _MenuSettings_
#define _MenuSettings_

#include <Arduino.h>

#define MENU_STORAGE_START 0
#define MENU_STORAGE_SIZE 17

class MenuSettings {
  public:
    static String getValue(byte blockIndex);
    static void setValue(byte blockIndex, String value);

  private:
    static byte memoryIndex(byte blockIndex);
};

#endif

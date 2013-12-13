#ifndef _RAMMenuSettings_
#define _RAMMenuSettings_

#include <Arduino.h>

#include "settings.h"

class RAMMenuSettings :
public MenuSettings {
  public:
    RAMMenuSettings(byte id);

    String getValue();
    void setValue(String value);

  private:
    String value;
};

#endif

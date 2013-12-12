#ifndef _MenuSettings_
#define _MenuSettings_

#include <Arduino.h>

class MenuSettings {
  public:
    virtual String getValue() = 0;
    virtual void setValue(String value) = 0;
};

#endif

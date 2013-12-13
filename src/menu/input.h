#ifndef _MenuInput_
#define _MenuInput_

#include <Arduino.h>

#include "Adafruit_RGBLCDShield.h"
#include "entry.h"
#include "settings.h"

class MenuInput :
public MenuEntry {
  public:
    MenuInput(String name, MenuEntry *parent, MenuSettings *settings);

    byte type();
    MenuEntry* render(Adafruit_RGBLCDShield *lcd, boolean init = false);

  protected:
    String storedValue;

    virtual void setupLcd(Adafruit_RGBLCDShield *lcd);
    virtual void teardownLcd(Adafruit_RGBLCDShield *lcd);
    virtual void handleInput(Adafruit_RGBLCDShield *lcd, byte button) = 0;

    void writeCharacter(Adafruit_RGBLCDShield *lcd, byte index, char character);

  private:
    MenuSettings *settings;
};

#endif

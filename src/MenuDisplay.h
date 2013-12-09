#include "Adafruit_RGBLCDShield.h"
#include "MenuEntry.h"

class MenuDisplay {
  public:
    MenuDisplay(Adafruit_RGBLCDShield *lcd);

    void enable(MenuEntry *entry);
    void disable();
    void render();

  private:
    Adafruit_RGBLCDShield *lcd;
    MenuEntry *currentEntry;
};

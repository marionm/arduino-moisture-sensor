#include "Adafruit_RGBLCDShield.h"
#include "MenuEntry.h"

class MenuDisplay {
  public:
    MenuDisplay(Adafruit_RGBLCDShield *lcd);

    void enable(MenuEntry *entry);
    void disable();
    void update();

  private:
    Adafruit_RGBLCDShield *lcd;
    MenuEntry *currentEntry;
    bool buttonPressed;

    void update(byte buttons, MenuEntry *entry);
    void renderScreen();
};

#include "entry.h"
#include "tier.h"

boolean MenuEntry::buttonPressed = false;
long MenuEntry::buttonHeldAt = 0;
byte MenuEntry::buttonHoldInterval = 250;

MenuEntry::MenuEntry(MenuEntry* (*_getParent)()) {
  getParent = _getParent;
}

byte MenuEntry::pressedButton(Adafruit_RGBLCDShield *lcd) {
  byte button = lcd->readButtons();
  if(button && !MenuEntry::buttonPressed) {
    MenuEntry::buttonPressed = true;
    return button;
  } else if(!button){
    MenuEntry::buttonPressed = false;
  }
  return 0;
}

byte MenuEntry::heldButton(Adafruit_RGBLCDShield *lcd) {
  byte button = lcd->readButtons();
  if(button && !MenuEntry::buttonPressed) {
    MenuEntry::buttonPressed = true;
    MenuEntry::buttonHeldAt = millis();
    MenuEntry::buttonHoldInterval = 250;
  } else if(!button){
    MenuEntry::buttonPressed = false;
    button = NULL;
  } else {
    long time = millis();
    if(time - MenuEntry::buttonHeldAt > MenuEntry::buttonHoldInterval) {
      MenuEntry::buttonHeldAt = time;
      MenuEntry::buttonHoldInterval = 100;
    } else {
      button = NULL;
    }
  }
  return button;
}

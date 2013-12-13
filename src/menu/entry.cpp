#include "entry.h"
#include "tier.h"

MenuEntry::MenuEntry(String _name, MenuEntry *_parent) {
  name        = _name;
  parent      = _parent;
  nextSibling = NULL;
  prevSibling = NULL;

  buttonPressed = true;

  if(parent && parent->type() == MENU_TIER) {
    ((MenuTier*)parent)->addChild(this);
  }
}

byte MenuEntry::pressedButton(Adafruit_RGBLCDShield *lcd) {
  byte button = lcd->readButtons();
  if(button && !buttonPressed) {
    buttonPressed = true;
    return button;
  } else if(!button){
    buttonPressed = false;
  }
  return NULL;
}

byte MenuEntry::heldButton(Adafruit_RGBLCDShield *lcd) {
  byte button = lcd->readButtons();
  if(button && !buttonPressed) {
    buttonPressed = true;
    buttonHeldAt = millis();
    buttonHoldInterval = 250;
  } else if(!button){
    buttonPressed = false;
    button = NULL;
  } else {
    long time = millis();
    if(time - buttonHeldAt > buttonHoldInterval) {
      buttonHeldAt = time;
      buttonHoldInterval = 100;
    } else {
      button = NULL;
    }
  }
  return button;
}

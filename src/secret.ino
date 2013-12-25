#include <Arduino.h>

#include "menu.h"
#include "notifier.h"
#include "sensor.h"
#include "settings.h"

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
MenuDisplay menu = MenuDisplay(&lcd);

Notifier notifier = Notifier();

void setup() {
  menu.enable(Menu::home());
}

void loop() {
  menu.render();

  // int value = Sensor::read();
  // byte threshold = MenuUtil::stringToByte(MenuSettings::getValue(THRESHOLD_ID));
  // if(value <= threshold) {
  //   notifier.sendNotificationIfInWindow();
  // }
}

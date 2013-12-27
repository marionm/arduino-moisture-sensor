#include <Arduino.h>

#include "menu.h"
#include "notifier.h"
#include "sensor.h"
#include "settings.h"

#define DISPLAY_MODE     true
#define BACKGROUND_MODE  false
#define DISPLAY_TIMEOUT  60000L
#define BACKGROUND_SLEEP 300000L

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
MenuDisplay menu = MenuDisplay(&lcd);

Notifier notifier = Notifier();

boolean mode;
long lastInputAt;

byte threshold;
boolean notified;

void setup() {
  Serial.begin(9600);

  notified = false;

  mode = DISPLAY_MODE;
  lastInputAt = millis();

  menu.enable(Menu::home());
}

void loop() {
  if(mode == DISPLAY_MODE) {
    menu.render();

    if(lcd.readButtons()) {
      lastInputAt = millis();
    } else if(millis() - lastInputAt > DISPLAY_TIMEOUT) {
      mode = BACKGROUND_MODE;
      menu.disable();
      threshold = MenuUtil::stringToByte(MenuSettings::getValue(THRESHOLD_ID));
    }

  } else {
    delay(BACKGROUND_SLEEP);

    int value = Sensor::read();
    if(notified && value > threshold) {
      notified = false;
    } else if(!notified && value <= threshold) {
      notified = notifier.sendNotificationsIfInWindow();
    }
  }
}

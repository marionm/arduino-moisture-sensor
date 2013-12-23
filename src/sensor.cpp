#include "sensor.h"

#define PIN_A 0
#define PIN_B A0

// From manual testing
#define SENSOR_MAX 700

int Sensor::read() {
  int value = getValue();

  // Prevent electromigration
  getValue(true);

  return value;
}

int Sensor::getValue(boolean reverse) {
  byte outPin = PIN_A;
  byte inPin  = PIN_B;
  if(reverse) {
    outPin = PIN_B;
    inPin  = PIN_A;
  }

  pinMode(inPin,  INPUT);
  pinMode(outPin, OUTPUT);

  digitalWrite(outPin, HIGH);

  delay(1000);

  long value = -1;
  if(!reverse) {
    value = analogRead(inPin);
    value = value * 100 / SENSOR_MAX;
    if(value > 100) {
      value = 100;
    }
  }

  digitalWrite(outPin, LOW);

  return value;
}

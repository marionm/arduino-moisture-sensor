#ifndef _Sensor_
#define _Sensor_

#include <Arduino.h>

class Sensor {
  public:
    static int read();

  private:
    static int getValue(boolean reverse = false);
};

#endif

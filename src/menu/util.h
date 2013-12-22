#ifndef _MenuUtil_
#define _MenuUtil_

#include <Arduino.h>

class MenuUtil {
  public:
    static char* byteToString(byte value);
    static byte stringToByte(char *string);
};

#endif

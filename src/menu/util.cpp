#include "util.h"

char* MenuUtil::byteToString(byte value) {
  byte length = 1;
  if(value > 0) {
    length = 0;
    byte clone = value;
    do {
      length += 1;
      clone /= 10;
    } while(clone > 0);
  }

  char string[length + 1];
  string[length] = '\0';

  for(byte i = length; i > 0; i--) {
    byte digit = value % 10;
    string[i - 1] = digit + 48;
    value /= 10;
  }

  return string;
}

byte MenuUtil::stringToByte(char *string) {
  byte value = 0;
  byte multiplier = 1;
  for(byte i = strlen(string); i > 0; i--) {
    char c = string[i - 1];
    if(c == '-') {
      value *= -1;
      break;
    } else if(c >= 48 && c <= 57) {
      value += (c - 48) * multiplier;
      multiplier *= 10;
    } else {
      break;
    }
  }
  return value;
}

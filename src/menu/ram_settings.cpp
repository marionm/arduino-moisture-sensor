#include "ram_settings.h"

RAMMenuSettings::RAMMenuSettings(byte id) {
  value = " ";
}

String RAMMenuSettings::getValue() {
  return value;
}

void RAMMenuSettings::setValue(String _value) {
  value = _value;
}

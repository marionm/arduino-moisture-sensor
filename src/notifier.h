#ifndef _Notifier_
#define _Notifier_

#include <Arduino.h>

#include "Adafruit_CC3000.h"

class Notifier {
  public:
    Notifier(
      byte nameSettingsIndex,
      byte emailSettingsIndex,
      byte phoneSettingsIndex,
      byte earliestTimeSettingsIndex,
      byte latestTimeSettingsIndex,
      byte ssidSettingsIndex,
      byte usernameSettingsIndex,
      byte passwordSettingsIndex
    );
    ~Notifier();

    boolean testConnection();
    void sendNotificationIfInWindow();

  private:
    Adafruit_CC3000 *wifi;
    byte nameSettingsIndex;
    byte emailSettingsIndex;
    byte phoneSettingsIndex;
    byte earliestTimeSettingsIndex;
    byte latestTimeSettingsIndex;
    byte ssidSettingsIndex;
    byte usernameSettingsIndex;
    byte passwordSettingsIndex;
    boolean connected;

    byte inNotificationWindow();
    void connect();
    void disconnect();
};

#endif

#ifndef _Notifier_
#define _Notifier_

#include <Arduino.h>

#include "Adafruit_RGBLCDShield.h"
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
      byte passwordSettingsIndex
    );
    ~Notifier();

    boolean testConnection(char resultMessage[16]);
    void sendNotificationsIfInWindow();
    void sendEmail();
    void sendText();

  private:
    Adafruit_CC3000 *wifi;
    byte nameSettingsIndex;
    byte emailSettingsIndex;
    byte phoneSettingsIndex;
    byte earliestTimeSettingsIndex;
    byte latestTimeSettingsIndex;
    byte ssidSettingsIndex;
    byte passwordSettingsIndex;
    boolean connected;

    byte inNotificationWindow();
    byte connect();
    void disconnect();
};

#endif

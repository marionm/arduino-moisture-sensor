#ifndef _Notifier_
#define _Notifier_

#include <Arduino.h>

#include "Adafruit_RGBLCDShield.h"
#include "Adafruit_CC3000.h"

class Notifier {
  public:
    Notifier();
    ~Notifier();

    boolean testConnection(char resultMessage[17]);
    void sendNotificationsIfInWindow();
    void sendEmail();
    void sendText();

  private:
    Adafruit_CC3000 *wifi;
    boolean connected;

    byte inNotificationWindow();
    byte connect();
    void disconnect();
};

#endif

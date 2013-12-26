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
    boolean sendNotificationsIfInWindow();
    void sendEmail();
    void sendText();

  private:
    Adafruit_CC3000 *wifi;
    boolean connected;

    byte inNotificationWindow();
    byte connect();
    Adafruit_CC3000_Client connectToHost(char *host, int port = 80);
    void disconnect();
};

#endif

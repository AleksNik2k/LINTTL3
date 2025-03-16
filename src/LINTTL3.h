#ifndef LINTTL3_H
#define LINTTL3_H

#include <Arduino.h>

class LINTTL3 {
  public:
    LINTTL3(Stream &serial, int slpPin, int inhPin);
    void begin();
    void sleep();
    void wakeUp();
    void sendLIN(byte data);
    byte receiveLIN();
    void setMasterMode(bool isMaster);

  private:
    Stream &_serial; // Объект для работы с UART (аппаратным или программным)
    int _slpPin;
    int _inhPin;
    bool _isMaster;
};

#endif
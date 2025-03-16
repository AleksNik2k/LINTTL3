#include "LINTTL3.h"

LINTTL3::LINTTL3(Stream &serial, int slpPin, int inhPin)
  : _serial(serial) {
  _slpPin = slpPin;
  _inhPin = inhPin;
  _isMaster = false;
}

void LINTTL3::begin() {
  pinMode(_slpPin, OUTPUT);
  pinMode(_inhPin, OUTPUT);

  digitalWrite(_slpPin, HIGH); // Выход из режима сна
  digitalWrite(_inhPin, LOW);  // По умолчанию не в режиме мастера
}

void LINTTL3::sleep() {
  digitalWrite(_slpPin, LOW); // Переход в режим сна
}

void LINTTL3::wakeUp() {
  digitalWrite(_slpPin, HIGH); // Выход из режима сна
}

void LINTTL3::sendLIN(byte data) {
  _serial.write(data); // Отправка данных на LIN-шину
}

byte LINTTL3::receiveLIN() {
  if (_serial.available()) {
    return _serial.read(); // Чтение данных с LIN-шины
  }
  return 0;
}

void LINTTL3::setMasterMode(bool isMaster) {
  _isMaster = isMaster;
  if (_isMaster) {
    digitalWrite(_inhPin, HIGH); // Активация режима мастера
  } else {
    digitalWrite(_inhPin, LOW);  // Деактивация режима мастера
  }
}
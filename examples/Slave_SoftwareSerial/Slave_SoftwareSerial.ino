#include <LINTTL3.h>
#include <SoftwareSerial.h>

// Определяем пины для подключения модуля LINTTL3
#define RX_PIN 10
#define TX_PIN 11
#define SLP_PIN 12
#define INH_PIN 13

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Создаем объект SoftwareSerial
LINTTL3 linModule(mySerial, SLP_PIN, INH_PIN); // Используем программный UART

void setup() {
  Serial.begin(9600); // Инициализация Serial для вывода в монитор порта
  mySerial.begin(9600); // Инициализация программного UART
  linModule.begin(); // Инициализация модуля
  linModule.setMasterMode(false); // Устанавливаем режим слейва
}

void loop() {
  // Чтение данных с LIN-шины
  String message = "";
  while (true) {
    byte receivedData = linModule.receiveLIN();
    if (receivedData == '\n') { // Конец строки
      break;
    }
    if (receivedData != 0) {
      message += (char)receivedData;
    }
  }

  // Обработка полученного сообщения
  if (message.length() > 0) {
    Serial.println("Получено сообщение от мастера: " + message);

    // Отправка ответа мастеру
    String response = "Привет Мастер, я твой подчиненный";
    for (int i = 0; i < response.length(); i++) {
      linModule.sendLIN(response[i]); // Отправка каждого символа строки
    }
    linModule.sendLIN('\n'); // Отправка символа новой строки
  }
}
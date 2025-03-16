#include <LINTTL3.h>

// Определяем пины для подключения модуля LINTTL3
#define SLP_PIN 12
#define INH_PIN 13

LINTTL3 linModule(Serial, SLP_PIN, INH_PIN); // Используем аппаратный UART

void setup() {
  Serial.begin(9600); // Инициализация Serial для вывода в монитор порта
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
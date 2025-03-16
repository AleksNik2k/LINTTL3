#include <LINTTL3.h>

// Определяем пины для подключения модуля LINTTL3
#define SLP_PIN 12
#define INH_PIN 13

LINTTL3 linModule(Serial, SLP_PIN, INH_PIN); // Используем аппаратный UART

void setup() {
  Serial.begin(9600); // Инициализация Serial для вывода в монитор порта
  linModule.begin(); // Инициализация модуля
  linModule.setMasterMode(true); // Устанавливаем режим мастера
}

void loop() {
  // Отправка данных на LIN-шину
  String message = "Привет, я мастер шины.";
  for (int i = 0; i < message.length(); i++) {
    linModule.sendLIN(message[i]); // Отправка каждого символа строки
  }
  linModule.sendLIN('\n'); // Отправка символа новой строки

  // Чтение ответа от слейва
  String response = "";
  while (true) {
    byte receivedData = linModule.receiveLIN();
    if (receivedData == '\n') { // Конец строки
      break;
    }
    if (receivedData != 0) {
      response += (char)receivedData;
    }
  }

  // Вывод ответа в монитор порта
  if (response.length() > 0) {
    Serial.println("Ответ от слейва: " + response);
  }

  delay(1000); // Задержка между отправкой данных
}
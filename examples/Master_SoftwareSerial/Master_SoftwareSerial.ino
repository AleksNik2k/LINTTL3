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
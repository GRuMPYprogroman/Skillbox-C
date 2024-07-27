#include <Arduino.h>

const int led_pin = 39;
const int button_pin = 17;
bool light_on = false;
int push_button_counter = 0;
bool last_button_state = LOW;
unsigned long last_debounce_time = 0;
const unsigned long debounce_delay = 100; //задержка для дребезга

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT); // Используем внешний подтягивающий резистор
  Serial.begin(115200); // Инициализация последовательного монитора
  last_button_state = digitalRead(button_pin); // Инициализация начального состояния кнопки
}

void loop() {
  // Чтение текущего состояния кнопки
  bool current_button_state = digitalRead(button_pin);

  // Проверка на изменение состояния кнопки
  if (current_button_state != last_button_state) {
    last_debounce_time = millis();
  }

  if ((millis() - last_debounce_time) > debounce_delay) {
    // Если состояние кнопки изменилось и оно стало HIGH
    if (current_button_state == HIGH && last_button_state == LOW) {
      ++push_button_counter;
      Serial.print("Button pressed: ");
      Serial.println(push_button_counter);

      if (push_button_counter == 3) {
        light_on = true;
        Serial.println("LED ON");
      }
      if (push_button_counter == 6) {
        light_on = false;
        push_button_counter = 0;
        Serial.println("LED OFF and counter reset");
      }
    }
  }

  // Запоминаем текущее состояние кнопки для следующей итерации
  last_button_state = current_button_state;

  // Управление светодиодом
  if (light_on) {
    digitalWrite(led_pin, HIGH);
  } 
  else {
    digitalWrite(led_pin, LOW);
  }
}
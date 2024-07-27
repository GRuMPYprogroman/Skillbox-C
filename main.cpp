#include <Arduino.h>

const int led_pin = 39;
const int button_pin = 18;
bool light_on = false;
int push_button_counter = 0;
int last_button_state = LOW;
bool button_pressed = false;
unsigned long last_pressed;

void setup() {
  pinMode(button_pin, INPUT); // Используем внешний подтягивающий резистор
  Serial.begin(115200); // Инициализация последовательного монитора
  pinMode(led_pin, OUTPUT);
  delay(1000); // Задержка для инициализации
}

void loop() {
  // Чтение текущего состояния кнопки
  bool current_button_state = digitalRead(button_pin);
  
  if (current_button_state && button_pressed == false && millis() - last_pressed > 300 )
    {
      ++push_button_counter;
      Serial.println(push_button_counter);
      button_pressed = true;
      last_pressed = millis();
    }
    if (!current_button_state && button_pressed == true)
    {
      button_pressed = false;
    }


  switch(push_button_counter)
  {
    case 2:
      light_on = true;
      break;
    case 4:
      light_on = false;
      push_button_counter = 0;
      break;
  }
  // Управление светодиодом
  if (light_on) {
    digitalWrite(led_pin, HIGH);
  } else {
    digitalWrite(led_pin, LOW);
  }
}
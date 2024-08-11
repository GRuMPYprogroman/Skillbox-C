#include <Arduino.h>
#include <string>
#include <list>

#define LED_PIN 39
#define CHANNEL_1 0
#define BUTTON_1 18

using str = std::string;
using list = std::list<int>;

// мощность свечения
int power = 4096;

// буффер для приема сообщений
str message = "";
std::list<int> buffer;

auto mean = [](std::list<int> buffer) -> int {
    int sum = 0;
    for (auto it = buffer.begin(); it != buffer.end(); ++it)
    {
      sum += *it;
    }
    return sum / buffer.size();
};

bool light_on = false;

void setup() {
  pinMode(BUTTON_1,INPUT);
  ledcSetup(CHANNEL_1, 5000, 8); // канал 0, частота 5kHz, разрешение 8 бит
  ledcAttachPin(LED_PIN, 0); // привязать канал 0 к пину
  Serial.begin(115200);
}

void loop() {

  if (buffer.size() == 4) 
  {
    Serial.print("Среднее по последним 4-ём сообщениям: ");
    Serial.println(mean(buffer));
    buffer.pop_front();
    delay(2000);
  }

  // читаем данные из серийного порта
  if (Serial.available() > 0) 
  {
    message = "";

    while(Serial.available() > 0)
    {
      message += str(1, char(Serial.read()));
      delay(500);
    }
    
    power = std::stoi(message);
    buffer.push_back(power);

    Serial.print("Recieved: power = ");
    Serial.println(power);
  }

  bool butt_1 = digitalRead(BUTTON_1);


  if(butt_1 == HIGH)
  {
    light_on = true;
  }

  if(light_on == true)
  {
    light_on = false;
    ledcWrite(CHANNEL_1, power);
    delay(1000);
  }
  else{
    ledcWrite(CHANNEL_1, 0);
  }
}
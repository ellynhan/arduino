#include <DHT11.h>
#include "Timer.h"
int pin=A2; //출력핀 아날로그
DHT11 dht11(pin);
Timer t; 
void setup(){
  Serial.begin(9600);
  t.every(2000, getValue); //2초 간격으로 getValue()함수 호출
}

float humi=0, temp=0;

void loop(){
  t.update(); //Millis를 이용해서 인터럽트하는 방식과 같음
}

void getValue(){ //온습도값 출력
  dht11.read(humi, temp);
  Serial.print("temperature: ");
  Serial.println(temp);
  Serial.print("humidity: ");
  Serial.println(humi);
}

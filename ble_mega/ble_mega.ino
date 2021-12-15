#include <SoftwareSerial.h>
String byteTmp = "";
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  while(Serial1.available()){//앱에서 아두이노로 데이터 전송하는 부분 
    byte data = Serial1.read(); //안드로이드에서 보낼 때 길이 수 맞춰서 보내도록 하기
    
    Serial.write(data);
    if(data == 'J'){
      Serial.println("J COME");
      byteTmp = "";
    }
    byteTmp+=char(data);
    Serial.println(byteTmp);
    if(byteTmp == "JACKPOT"){
      Serial.println("IT'S JACKPOT!!");
      byteTmp = "";
    }
  }
}

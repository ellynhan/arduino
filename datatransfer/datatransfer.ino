#include <SoftwareSerial.h>
#include <DHT11.h>
#include "Timer.h"

//communication with server
const int rxPin = 3;
const int txPin = 2;
SoftwareSerial mySerial(rxPin, txPin);

//watering time configuration
unsigned long day = 86400000;
unsigned long waterInterval = day * 7; //initial 7 days. 
unsigned long setTime = millis();
int waterAmount = 1;

//moter
int pumpPin = 9;

//Traffic LED
int redPin = 11;
int yellowPin = 12;
int greenPin = 13; 

//sensor
int waterPin = A0;
int soilPin = A1;
int dhtPin = A2;
int illuPin = A3;

//Relay Led
int relLedPin1 = 4;
int relLedPin2 = 5;
int relLedPin3 = 6;
int relLedPin4 = 7;

DHT11 dht11(dhtPin);

Timer rt; // request timer

void setup() {
  Serial.begin(9600);   //시리얼모니터
  mySerial.begin(9600);

  pinMode(redPin,OUTPUT);
  pinMode(yellowPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(pumpPin,OUTPUT);
  pinMode(relLedPin1,OUTPUT);
  pinMode(relLedPin2,OUTPUT);
  pinMode(relLedPin3,OUTPUT);
  pinMode(relLedPin4,OUTPUT);
  
  rt.every(9000,getSensor); //9초마다 서버 연결
}


String response;
int startIdx; 
float humi=0, temp=0, soil=0;
int illu=40, wale=40; 
int ledval=4,wcval=0; //led개수, waterCycle. 
int checkOnce=0;

void loop() {
  rt.update();
  if(mySerial.available()){
    response+=char(mySerial.read());
//    Serial.write(mySerial.read());
    if(response.endsWith("Unlink")){
      Serial.println(response);
      startIdx = response.indexOf("[[");
      if(startIdx != -1){
        ledval = (response.substring(startIdx+2,startIdx+3)).toInt();
        wcval = (response.substring(startIdx+4,startIdx+5)).toInt();
        Serial.println(ledval);
        Serial.println(wcval);
        if(wcval != 0){
          waterInterval = day * wcval;
          checkOnce = 0;
        }else if(checkOnce == 0){
          waterPlant();
          checkOnce++;
        }
      }
    }
  }
  
//  Serial.println(ledval);
  switch(ledval){
    case 1:
      digitalWrite(relLedPin1, HIGH);
      digitalWrite(relLedPin2, LOW);
      digitalWrite(relLedPin3, LOW);
      digitalWrite(relLedPin4, LOW);
      break;
    case 2:
      digitalWrite(relLedPin1, HIGH);
      digitalWrite(relLedPin2, HIGH);
      digitalWrite(relLedPin3, LOW);
      digitalWrite(relLedPin4, LOW);
      break;
    case 3:
      digitalWrite(relLedPin1, HIGH);
      digitalWrite(relLedPin2, HIGH);
      digitalWrite(relLedPin3, HIGH);
      digitalWrite(relLedPin4, LOW);
      break;
    case 4:
      digitalWrite(relLedPin1, HIGH);
      digitalWrite(relLedPin2, HIGH);
      digitalWrite(relLedPin3, HIGH);
      digitalWrite(relLedPin4, HIGH);
      break;
    case 0:
      digitalWrite(relLedPin1, LOW);
      digitalWrite(relLedPin2, LOW);
      digitalWrite(relLedPin3, LOW);
      digitalWrite(relLedPin4, LOW);
      break;
  }

  if(setTime + waterInterval < millis()){ // 주기가 아니다
    if(soil<30){ //흙이 건조하다
      waterPlant();
      waterAmount+=1;
    }
  }else{ // 주기이다. 
    setTime = millis();
    if(soil<40){//흙이 건조하다 (적당)
      waterPlant();
    }else if(soil>65){ //흙 습도가 너무 높다 (과다)
      if(waterAmount!=1){
        waterAmount -=1;
      }
    }else{// 물이 조금 많았던것같다 (약간 많음)
      if(waterAmount!=1){
        waterAmount -= 1;
      }
      waterPlant();
    }
  }
}

//물 주는 함수 
void waterPlant(){
  for(int i=0; i<waterAmount*2; i++){
    digitalWrite(pumpPin,HIGH);
    delay(400);
    digitalWrite(pumpPin,LOW);
    delay(100);
  }
}

//센서 값 받는 함수
void getSensor(){
  dht11.read(humi, temp);
  soil = analogRead(soilPin);
  soil = map(soil,1023,0,0,100);
  wale = analogRead(waterPin);
  wale = map(wale,0,1023,0,100);
  illu = analogRead(illuPin);
  digitalWrite(greenPin,LOW);
  digitalWrite(yellowPin,LOW);
  digitalWrite(redPin,LOW);
  if(wale>65){
    digitalWrite(greenPin,HIGH);
  }else if(wale>45){
    digitalWrite(yellowPin,HIGH);
  }else{
    digitalWrite(redPin,HIGH);
  }
  requestPOST();
}

//서버와 통신.
 void requestPOST(){
  response = "";
  String url = "GET /mydata?humi="+(String)humi+"&illu="+(String)illu+"&temp="+(String)temp+"&water="+(String)wale+"&soil="+(String)soil+" HTTP/1.1\r\n";
  String host = "Host: ip주소\r\n";
  String closing = "Connection: close\r\n\r\n";
  int len = url.length()+host.length()+closing.length();
  String cmd = url+host+closing;
  mySerial.print("AT+CIPSTART=\"TCP\",\"192.168.43.174\",7777\r\n");
  mySerial.print("AT+CIPSEND="+String(len)+"\r\n");
  mySerial.print(cmd);
}

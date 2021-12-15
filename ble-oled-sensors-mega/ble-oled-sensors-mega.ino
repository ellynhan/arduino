#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>
#include <DHT11.h>
#include "Timer.h"

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

//variables
String byteToString = "";
String outputString = "";
String oledMessage = "aaa";
int androidInputValue[3] = {0,0,0}; //led, timer, coolingfan
int androidInputCount = 0;
bool commandActive = false;
float humidity = 0;
float temperature = 0;
float soilmoisture = 0;

//pin
int pin_coolingfan = 6;
int pin_led[3] = {7,8,9};
int pin_soil = A0;
int pin_dht = A2;

//set utils
Timer timer;
DHT11 dht11(pin_dht);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  drawDisplay("Set up...");
  timer.every(5000,getSensorValue);
}

void loop() {
  timer.update();
  oledMessage = "T:"+(String)temperature+"C\nH:"+(String)humidity+"%\nS:"+(String)soilmoisture+"%";
  drawDisplay(oledMessage);
  
  while(Serial1.available()) {//안드로이드 앱에서 아두이노로 데이터 전송
    byte data = Serial1.read();//바이트 단위로 읽힘
    
    //JACKPOT의 J가 들어오면 byteToString 값 초기화
    if(data == 'J'){ 
      byteToString = "";
    }
    
    byteToString += char(data); //char로 형변환 안하면 숫자만 저장됨

    //커맨드 들어옴
    if(byteToString == "JACKPOT"){
      Serial.println(byteToString);
      commandActive = true;
      byteToString = "";
      continue;
    }

    //JACKPOT 커맨드 받고 뒤 값 3개 받는 과정
    if(commandActive){
      androidInputValue[androidInputCount] = data - 48;//어차피 숫자라 형변환 필요 없음, 아스키코드 형태라서 -48이나 -'0'해야함
      androidInputCount += 1;
    }

    //값 3개 다 받았으면 출력
    if(androidInputCount == 4){
      androidInputCount = 0;
      commandActive = false;
      for(int i=0; i<4; i++){
        Serial.println(androidInputValue[i]);
      }
    }
  }
}

void getSensorValue(){
  delay(2000);
  soilmoisture = analogRead(pin_soil);
  soilmoisture = ((1023-soilmoisture)/1023)*100;
  dht11.read(humidity, temperature);
}

void drawDisplay(String message){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.print(message);
  display.display(); 
}

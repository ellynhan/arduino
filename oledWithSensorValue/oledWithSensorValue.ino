#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT11.h>
#include "Timer.h"
//pin setting
int soil = A0;
DHT11 dht11(A2);
Timer t;

//value initialize
float humi=0, temp=0,soilmoisture=0;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  t.every(2000,getValue);
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("T:"+(String)temp+"C ");
  display.println("H:"+(String)humi+"% ");
  display.println("S:"+(String)soilmoisture+"% ");
  display.display(); 
}

void loop() {
  t.update();
  drawDisplay();
}

void getValue(){
  delay(2000);
  soilmoisture = analogRead(soil);
  soilmoisture = ((1023-soilmoisture)/1023)*100;
  dht11.read(humi, temp);
}

void drawDisplay(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
//  Serial.print("temperature: ");
//  Serial.println(temp);
//  Serial.print("humidity: ");
//  Serial.println(humi);
//  Serial.print("read sensor value: ");
//  Serial.println(soilmoisture);
  display.println("T:"+(String)temp+"C ");
  display.println("H:"+(String)humi+"% ");
  display.println("S:"+(String)soilmoisture+"% ");
  display.display(); 
  
}

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(4,5); //TX, RX 
String byteToString = "";
int inputValue[3] = {1,2,3};
bool commandActive = false;
int inputCount = 0;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600); 
}

void loop() {
 while(BTSerial.available()) {//안드로이드 앱에서 아두이노로 데이터 전송
    byte data = BTSerial.read();//바이트 단위로 읽힘
    
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
      inputValue[inputCount] = data - 48;//어차피 숫자라 형변환 필요 없음, 아스키코드 형태라서 -48이나 -'0'해야함
      inputCount += 1;
    }

    //값 3개 다 받았으면 출력
    if(inputCount == 3){
      inputCount = 0;
      commandActive = false;
      for(int i=0; i<3; i++){
        Serial.println(inputValue[i]);
      }
    }
  }
}

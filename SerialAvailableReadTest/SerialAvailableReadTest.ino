void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()>0){ //수신된 데이터 존재 여부 확인
    byte data = Serial.read();//바이트 단위로 읽기
    Serial.print("Echo back: ");
    Serial.write(data);//문자출력
    Serial.print(" ");
    Serial.println(data); //ASCII 값 출력
  }
}

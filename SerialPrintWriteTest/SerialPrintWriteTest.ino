void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Test String");
  delay(1000);
  byte data = 65;
  Serial.println(data);
  delay(1000);
  Serial.write(data);//write는 char형태로 출력하는구나
  delay(1000);
  Serial.println(data);
  delay(1000);
}

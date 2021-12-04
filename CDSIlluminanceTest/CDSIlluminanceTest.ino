void setup() {
  Serial.begin(9600);
}

void loop() {
  int a = analogRead(A0);
  Serial.println(a); //가장 어두울때 1023 가장 짐밝을때0, 집안 LED에서 800~900사이 값을 가
  delay(1000);
}

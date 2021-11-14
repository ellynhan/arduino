int soil = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(soil);
  Serial.print("read sensor value: ");
  Serial.println(value); //수분이 없으면 1023, 수분이 높을수록 0
  delay(1000);
}

int pin = 6;

void setup() {
  pinMode(pin,OUTPUT);

}

void loop() {
  digitalWrite(pin,255);
  delay(3000);
  digitalWrite(pin,LOW);
  delay(3000);
  digitalWrite(pin,100);
  delay(3000);
  digitalWrite(pin,LOW);
  delay(3000);
}

int waterPumpPin = 4;


void setup() {
  pinMode(waterPumpPin,OUTPUT);
}

void loop() {
  digitalWrite(waterPumpPin,HIGH);
  delay(2000);
  digitalWrite(waterPumpPin,LOW);
  delay(3000);

}

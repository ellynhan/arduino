
int relLedPin1 = 4;
int relLedPin2 = 5;
int relLedPin3 = 6;
int relLedPin4 = 7;

void setup() {
  pinMode(relLedPin1,OUTPUT);
  pinMode(relLedPin2,OUTPUT);
  pinMode(relLedPin3,OUTPUT);
  pinMode(relLedPin4,OUTPUT);
}

void loop() {
  digitalWrite(relLedPin1, LO그W);
  digitalWrite(relLedPin2, LOW);
  digitalWrite(relLedPin3, HIGH);
  digitalWrite(relLedPin4, HIGH);
  
  delay(2000);
  digitalWrite(relLedPin1, HIGH);
  digitalWrite(relLedPin2, HIGH);
  digitalWrite(relLedPin3, LOW);
  digitalWrite(relLedPin4, LOW);
  delay(1000);
}

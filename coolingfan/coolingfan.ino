int leftfan = 5;
int rightfan = 4;

void setup() {
    pinMode(leftfan, OUTPUT);
    pinMode(rightfan, OUTPUT);
    Serial.begin(9600); // 통신 속도 설정// put your setup code here, to run once:

}

void loop() {
    digitalWrite(leftfan, HIGH);
    digitalWrite(rightfan, HIGH);
    delay(3000);
    digitalWrite(leftfan,LOW);
    digitalWrite(rightfan,LOW);
    delay(3000);
}

const int POTPIN = A3;
void setup() {
  // put your setup code here, to run once:
    analogSetWidth(10);
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    int potVal = analogRead(POTPIN);
    Serial.println(potVal);
}

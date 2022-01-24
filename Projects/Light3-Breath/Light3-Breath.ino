const int LEDPIN = 16;
const long FREQ = 5000;
const int LEDCH = 0;
const int RES = 8;
void setup() {
  // put your setup code here, to run once:
    ledcSetup(LEDCH, FREQ, RES);
    ledcAttachPin(LEDPIN, LEDCH);
    pinMode(LEDPIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    for(int i = 0; i <= 255; i += 5)
    {
        ledcWrite(LEDCH, i);
        delayMicroseconds(1);
    }
    for(int i = 255; i >= 0; i -= 5)
    {
        ledcWrite(LEDCH, i);
        delayMicroseconds(1);
    }
}

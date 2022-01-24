const int PIRPIN = 14;
const int LEDPIN = 12;
bool flag = 0;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(PIRPIN, INPUT);
    pinMode(LEDPIN, OUTPUT);
    attachInterrupt(PIRPIN, PIR_Detect, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
    if (flag)
    {
        digitalWrite(LEDPIN, HIGH);
    }
    else
    {
        digitalWrite(LEDPIN, LOW);
    }
}

void PIR_Detect()
{
    flag = !flag;
}

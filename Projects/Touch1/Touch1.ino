const int THRESHOLD = 10;
const int TOUCHPIN = T4;
bool touchDetected = 0;
void GetTouch()
{
    touchDetected = 1;
}
void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    touchAttachInterrupt(TOUCHPIN, GetTouch, THRESHOLD);
}

void loop() {
  // put your main code here, to run repeatedly:
    int touchVal = touchRead(TOUCHPIN);
    Serial.print("Value: ");
    Serial.println(touchVal);
    if (touchDetected)
    {
        touchDetected = 0;
        Serial.println("Touch Detected");
    }
    delay(100);
}

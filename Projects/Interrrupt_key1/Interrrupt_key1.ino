const int KEYPIN = 15;
int num = 0;
bool flag = 0;
void Echo()
{
    flag = 1;
    num++;
}
void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(KEYPIN, INPUT);
    attachInterrupt(KEYPIN, Echo, CHANGE);
}

void loop()
{
    // put your main code here, to run repeatedly:
    if (flag) {
        Serial.println(num);
        num = 0;
    }
    flag = 0;
}

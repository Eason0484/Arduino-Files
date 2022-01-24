const int KEYPIN = 26;
const int LEDPIN = 12;
int preKeyVal = 1;
int preKeyState = 1;
bool keyFlag = 0;
unsigned int preTime = 0;
int debounceDelay = 10;

void GetKeyState();

void setup()
{
    pinMode(KEYPIN, INPUT);
    pinMode(LEDPIN, OUTPUT);
}

void loop()
{
    GetKeyState();
    digitalWrite(LEDPIN, keyFlag);
}

void GetKeyState()
{
    int keyVal = digitalRead(KEYPIN);
    if (keyVal != preKeyVal)
    {
        preTime = millis();
        preKeyVal = keyVal;
    }
    if ((millis() - preTime) > debounceDelay)
    {
        if (keyVal != preKeyState)
        {
            preKeyState = keyVal;
            if (keyVal == HIGH)
            {
                keyFlag = !keyFlag;
            }
        }
    }
}

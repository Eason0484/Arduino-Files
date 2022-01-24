const int DATAPIN = 12;
const int CLOCKPIN = 13;
const int LATCHPIN = 14;
const int KEYPIN = 4;
int preKeyVal = 0;
int preKeyState = 1;
bool keyFlag = 0;
bool keyState = keyFlag;
bool countFlag = 0;
unsigned int preTime = 0;
int debounceDelay = 10;
unsigned int num = 0;

const byte NUM[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xfe, 0xf6, 0x01};

void SpecialDigitDisplay(int digit, int num)
{
    byte val = 0;
    bitSet(val, digit - 1);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, val);
    shiftOut(DATAPIN, CLOCKPIN, LSBFIRST, ~NUM[num]);
    digitalWrite(LATCHPIN, HIGH);
    digitalWrite(LATCHPIN, LOW);
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

void DisplayNum(int num)
{
    int results[4];
    results[0] = num / 1000;
    num = num % 1000;
    results[1] = num / 100;
    num = num % 100;
    results[2] = num / 10;
    results[3] = num % 10;
    for (int i = 0; i <= 3; i++)
    {
        SpecialDigitDisplay(i + 1, results[i]);
    }
}

void setup()
{
    pinMode(DATAPIN, OUTPUT);
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(LATCHPIN, OUTPUT);
    pinMode(KEYPIN, INPUT);

    digitalWrite(CLOCKPIN, LOW);
    digitalWrite(LATCHPIN, LOW);
}

void loop()
{
    GetKeyState();
    if (keyState != keyFlag && keyFlag == 0)
    {
        num++;
    }
    keyState = !keyState;
    DisplayNum(num);
}

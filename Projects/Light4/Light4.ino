const int DATAPIN = 12;
const int CLOCKPIN = 13;
const int LATCHPIN = 14;
const int LEDCH = 0;
const int RES = 10;
const int LEDPIN = 2;
const int POTPIN = 4;
const int FREQ = 5000;

long oldTime = millis();

const byte NUMS[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xfe, 0xf6, 0x01};

void SpecialDigitDisplay(int, int);
void DisplayNum(int);
void Breath(int);

void setup()
{
    pinMode(DATAPIN, OUTPUT);
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(LATCHPIN, OUTPUT);
    pinMode(LEDPIN, OUTPUT);
    pinMode(POTPIN, INPUT);

    ledcSetup(LEDCH, FREQ, RES);
    ledcAttachPin(LEDPIN, LEDCH);

    analogSetWidth(10);
}

void loop()
{
    int i;
    for (i = 0; i <= 1023;)
    {
        ledcWrite(LEDCH, map(i, 0, 1023, 0, 511));
        DisplayNum(i);
        if (millis() - oldTime >= analogRead(POTPIN))
        {
            i += 10;
            oldTime = millis();
        }
    }
    for (i = 1023; i >= 0;)
    {
        ledcWrite(LEDCH, map(i, 0, 1023, 0, 511));
        DisplayNum(i);
        if (millis() - oldTime >= analogRead(POTPIN))
        {
            i -= 10;
            oldTime = millis();
        }
    }
}

void SpecialDigitDisplay(int digit, int num)
{
    byte val = 0;
    bitSet(val, digit - 1);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, val);
    shiftOut(DATAPIN, CLOCKPIN, LSBFIRST, ~NUMS[num]);
    digitalWrite(LATCHPIN, HIGH);
    digitalWrite(LATCHPIN, LOW);
}

void DisplayNum(int num)
{
    int results[4];
    results[0] = num / 1000;
    num %= 1000;
    results[1] = num / 100;
    num %= 100;
    results[2] = num / 10;
    results[3] = num % 10;
    for (int i = 0; i <= 3; i++)
    {
        SpecialDigitDisplay(i + 1, results[i]);
    }
}

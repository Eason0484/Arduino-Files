const int DATAPIN = 12;
const int CLOCKPIN = 13;
const int LATCHPIN = 14;
const int POTPIN = 4;
int i = 999;
unsigned int oldTime = millis();

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
    pinMode(POTPIN, INPUT);

    analogSetWidth(10);

    Serial.begin(9600);

    digitalWrite(CLOCKPIN, LOW);
    digitalWrite(LATCHPIN, LOW);
}

void loop()
{
    int potVal = analogRead(POTPIN);

    if (millis() - oldTime >= potVal)
    {
        oldTime = millis();
        i++;
    }
    if (i > 9999)
    {
        i = 999;
    }
    DisplayNum(i);
}

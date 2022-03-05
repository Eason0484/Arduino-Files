const int DATAPIN = 12;
const int CLOCKPIN = 13;
const int LATCHPIN = 14;

long oldTime = millis();
int delayTime = 100;
bool state = 0;
String receData = "";

const byte NUMS[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xfe, 0xf6, 0x01};

void SpecialDigitdisplay(int, int);
void DisplayNum(int);
void ReceiveDelayTime();

void setup()
{
    pinMode(DATAPIN, OUTPUT);
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(LATCHPIN, OUTPUT);

    Serial.begin(9600);
}

void loop()
{
    for (int i = 0; i <= 9999;)
    {
        ReceiveDelayTime();
        DisplayNum(i);
        if (millis() - oldTime >= delayTime)
        {
            oldTime = millis();
            i++;
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
    return;
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
    return;
}

void ReceiveDelayTime()
{
    if (Serial.available() > 0)
    {
        char dataBuff = Serial.read();
        if (dataBuff == '\r')
        {
            delayTime = receData.toInt();
            receData = "";
            Serial.println(delayTime);
        }
        else
        {
            receData += dataBuff;
        }
    }
}

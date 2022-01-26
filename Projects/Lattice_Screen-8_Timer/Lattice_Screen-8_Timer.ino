const int PUSHBUTTON = 32;
const int DATAPIN = 12;
const int CLOCKPIN = 13;
const int LATCHPIN = 14;

byte dataRow, dataCol;
unsigned int oldTime;
int valH = 11, valM = 11, valS = 11;

byte pic[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
byte picNum[10][5] = {
    {0x8, 0xa, 0xa, 0xa, 0x8},
    {0xd, 0x9, 0xd, 0xd, 0x8},
    {0x8, 0xe, 0x8, 0xb, 0x8},
    {0x8, 0xe, 0x8, 0xe, 0x8},
    {0xa, 0xa, 0x8, 0xe, 0xe},
    {0x8, 0xb, 0x8, 0xe, 0x8},
    {0x8, 0xb, 0x8, 0xa, 0x8},
    {0x8, 0xe, 0xd, 0xd, 0xd},
    {0x8, 0xa, 0x8, 0xa, 0x8},
    {0x8, 0xa, 0x8, 0xe, 0x8}
};

void setup()
{
    LED_Init();
    pinMode(PUSHBUTTON, INPUT);
    oldTime = millis();
}

void loop()
{
    DrawPic();

    if (millis() - oldTime >= 1000)
    {
        oldTime = millis();
        valS += 1;
        if (valS >= 60)
        {
            valS = 0;
            valM += 1;

            if (valM >= 60)
            {
                valM = 0;
                valH += 1;

                if (valH >= 24)
                {
                    valH = 0;
                }
            }
            ShowBin(valH, valM);
        }
        if (digitalRead(PUSHBUTTON))
        {
            pic[0] &= ~(1 << 7);
            pic[1] |= 1 << 7;
            ShowNum(valH);
        }
        else
        {
            pic[1] &= ~(1 << 7);
            pic[0] |= 1 << 7;
            ShowNum(valM);
        }
    }
}

void LED_Init(void)
{
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(LATCHPIN, OUTPUT);
    pinMode(DATAPIN, OUTPUT);
    digitalWrite(CLOCKPIN, LOW);
    digitalWrite(LATCHPIN, LOW);
}

void DrawPic()
{
    for (int i = 0; i <= 7; i++)
    {
        dataRow = 1 << i;
        dataCol = pic[i];
        shiftOut(DATAPIN, CLOCKPIN, LSBFIRST, dataCol);
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, dataRow);
        digitalWrite(LATCHPIN, HIGH);
        digitalWrite(LATCHPIN, LOW);
    }
}


void ShowBin(int h, int m)
{
    pic[0] = ~h;
    pic[1] = ~m;
}

void ShowNum(int val)
{
    for (int i = 3; i < 8; i++)
    {
        pic[i] = picNum[val / 10][i - 3];
        pic[i] = pic[i] << 4 | picNum[val % 10][i - 3];
    }
}

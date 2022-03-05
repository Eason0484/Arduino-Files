const int LEDPIN = 16;
const long FREQ = 5000;
const int LEDCH = 0;
const int RES = 10;
const int DATAPIN = 12;
const int CLOCKPIN = 13;
const int LATCHPIN = 14;
const int POTPIN = A0;
unsigned long long oldTime = 0;

bool flagShow = 0;

byte dataRow, dataCol;

int pic1[8] = {
    // Picture1
    0b10011001,
    0b00000000,
    0b00000000,
    0b00000000,
    0b10000001,
    0b11000011,
    0b11100111,
    0b11111111,
};
int pic2[8] = {
    // Picture2
    0b11111111,
    0b11011011,
    0b11000011,
    0b10000001,
    0b11000011,
    0b11100111,
    0b11111111,
    0b11111111,
};
void setup()
{
    pinMode(DATAPIN, OUTPUT);
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(LATCHPIN, OUTPUT);
    pinMode(POTPIN, INPUT);
    pinMode(LEDPIN, OUTPUT);

    digitalWrite(CLOCKPIN, LOW);
    digitalWrite(LATCHPIN, LOW);

    analogSetWidth(10);

    ledcSetup(LEDCH, FREQ, RES);
    ledcAttachPin(LEDPIN, LEDCH);
}

void loop()
{
    int potVal = analogRead(POTPIN);
    ledcWrite(LEDCH, potVal);
    if (millis() - oldTime >= potVal)
    {
        flagShow = !flagShow;
        oldTime = millis();
    }
    for (int i = 0; i <= 7; i++)
    {
        dataRow = 1 << i;
        if (flagShow)
        {
            dataCol = pic1[i];
        }
        else
        {
            dataCol = pic2[i];
        }
        LCD_Display();
    }
}

void LCD_Display()
{
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, dataCol);
    shiftOut(DATAPIN, CLOCKPIN, LSBFIRST, dataRow);
    digitalWrite(LATCHPIN, HIGH);
    digitalWrite(LATCHPIN, LOW);
}

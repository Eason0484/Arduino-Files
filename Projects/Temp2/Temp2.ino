const int DATAPIN = 12;
const int CLOCKPIN = 13;
const int LATCHPIN = 14;
const int POTPIN = 4;

int flagShow = 0;
unsigned int oldTime = 0;
byte dataCol, dataRow;

int pic[10][8] = {
    {
        0b11111111,
        0b11000111,
        0b11110111,
        0b11110111,
        0b11110111,
        0b11110111,
        0b11110111,
        0b11000011
    },
    {
        0b11111111,
        0b11000011,
        0b11111011,
        0b11111011,
        0b11000011,
        0b11011111,
        0b11011111,
        0b11000011
    },
    {
        0b11111111,
        0b11000011,
        0b11111011,
        0b11111011,
        0b11000011,
        0b11111011,
        0b11111011,
        0b11000011
    },
    {
        0b11111111,
        0b11010111,
        0b11010111,
        0b11010111,
        0b11000011,
        0b11110111,
        0b11110111,
        0b11110111
    },
    {
        0b11111111,
        0b11000011,
        0b11011111,
        0b11011111,
        0b11000011,
        0b11111011,
        0b11111011,
        0b11000011
    },
    {
        0b11111111,
        0b11000011,
        0b11011111,
        0b11011111,
        0b11000011,
        0b11011011,
        0b11011011,
        0b11000011
    },
    {
        0b11111111,
        0b11000011,
        0b11111011,
        0b11110111,
        0b11110111,
        0b11101111,
        0b11101111,
        0b11101111
    },
    {
        0b11111111,
        0b11000011,
        0b11011011,
        0b11011011,
        0b11000011,
        0b11011011,
        0b11011011,
        0b11000011
    },
    {
        0b11111111,
        0b11000011,
        0b11011011,
        0b11011011,
        0b11000011,
        0b11111011,
        0b11111011,
        0b11000011
    },
    {
        0b11111111,
        0b11000011,
        0b11011011,
        0b11011011,
        0b11011011,
        0b11011011,
        0b11011011,
        0b11000011
    }
};

void LCD_Display()
{
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, dataCol);
    shiftOut(DATAPIN, CLOCKPIN, LSBFIRST, dataRow);
    digitalWrite(LATCHPIN, HIGH);
    digitalWrite(LATCHPIN, LOW);
}

void setup()
{
    pinMode(DATAPIN, OUTPUT);
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(LATCHPIN, OUTPUT);

    analogSetWidth(10);

    digitalWrite(CLOCKPIN, LOW);
    digitalWrite(LATCHPIN, LOW);
}

void loop()
{
    if (millis() - oldTime >= analogRead(POTPIN))
    {
        if (flagShow >= 9)
        {
            flagShow = 0;
        }
        else
        {
            flagShow++;
        }
        oldTime = millis();
    }
    for (int i = 0; i <= 7; i++)
    {
        dataRow = 1 << i;
        dataCol = pic[flagShow][i];
        LCD_Display();
    }
}

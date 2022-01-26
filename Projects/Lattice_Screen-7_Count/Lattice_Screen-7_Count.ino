const int DATAPIN = 12;
const int CLOCKPIN = 13;
const int LATCHPIN = 14;
const int POTPIN = 4;

int flagShow = 0;
unsigned long oldTime = 0;
byte dataRow, dataCol;

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

void setup() {
    pinMode(LATCHPIN, OUTPUT);
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(DATAPIN, OUTPUT);
    
    digitalWrite(CLOCKPIN, LOW);
    digitalWrite(LATCHPIN, LOW);
    
    Serial.begin(9600);

    analogSetWidth(10);
}

void loop() {
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
    for (int j = 0; j <= 7; j++)
    {
        dataRow = 1 << j;
        dataCol = pic[flagShow][j];
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

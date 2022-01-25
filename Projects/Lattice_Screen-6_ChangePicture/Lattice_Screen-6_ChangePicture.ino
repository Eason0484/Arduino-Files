const int DATAPIN = 12;
const int CLOCKPIN = 13;
const int LATCHPIN = 14;
const int POTPIN = 4;

int flagShow = 0;
unsigned long oldTime = 0;
byte dataRow, dataCol;

int pic1[8] = { //Picture1
    0b10011001,
    0b00000000,
    0b00000000,
    0b00000000,
    0b10000001,
    0b11000011,
    0b11100111,
    0b11111111,
};

int pic2[8] = { //Picture2
    0b11111111,
    0b11011011,
    0b11000011,
    0b10000001,
    0b11000011,
    0b11100111,
    0b11111111,
    0b11111111,
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
    int potVal = analogRead(POTPIN);
    if (millis() - oldTime >= potVal)
    {
        oldTime = millis();
        flagShow = !flagShow;
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

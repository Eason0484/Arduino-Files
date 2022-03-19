const int DATAPIN = 12;
const int CLOCKPIN = 13;
const int LATCHPIN = 14;
const int POTPIN = A0;

int flagShow = -1;
unsigned long oldTime = 0;
byte dataRow, dataCol;

int pic1[8] = {0xef, 0xc7, 0x83, 0x01, 0xef, 0xef, 0xef, 0xff};
int pic2[8] = {
    0b11111111,
    0b11110111,
    0b11110111,
    0b11110111,
    0b10000000,
    0b11000001,
    0b11100011,
    0b11110111,
};
int pic3[8] = {
    0b00000000,
    0b01111110,
    0b01111110,
    0b01111110,
    0b01111110,
    0b01111110,
    0b01111110,
    0b00000000,
};

void setup()
{
    pinMode(LATCHPIN, OUTPUT);
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(DATAPIN, OUTPUT);

    digitalWrite(CLOCKPIN, LOW);
    digitalWrite(LATCHPIN, LOW);

    Serial.begin(9600);

    analogSetWidth(10);
}
void loop()
{
    String receData = "";
    if (Serial.available() > 0)
    {
        char dataBuff = Serial.read();
        if (dataBuff != '\r')
        {
            receData += dataBuff;
        }
        if (receData == "W")
        {
            flagShow = 1;
            Serial.println("UPPER");
        }
        if (receData == "Z")
        {
            flagShow = 0;
            Serial.println("DOWN");
        }
    }
    for (int i = 0; i <= 7; i++)
    {
        dataRow = 1 << i;
        if (flagShow)
        {
            dataCol = pic1[i];
        }
        if (flagShow == 0)
        {
            dataCol = pic2[i];
        }
        if (flagShow == -1)
        {
            dataCol = pic3[i];
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

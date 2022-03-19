int pic0[8] = {
    0b00000000,
    0b01111110,
    0b01111110,
    0b01111110,
    0b01111110,
    0b01111110,
    0b01111110,
    0b00000000,
};

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

const int DATAPIN = 12;
const int CLOCKPIN = 13;
const int LATCHPIN = 14;

byte dataCol, dataRow;
long long oldTime = 0;
short flagShow = -1;
int timeB = 1000, timeS = 1000;
String receData = "";

void setup()
{
    pinMode(DATAPIN, OUTPUT);
    pinMode(LATCHPIN, OUTPUT);
    pinMode(CLOCKPIN, OUTPUT);

    Serial.begin(9600);
}

void loop()
{
    if (Serial.available() > 0)
    {
        flagShow = 1;
        char readBuff = Serial.read();
        if (readBuff != '\r')
        {
            receData += readBuff;
        }
        else
        {
            int posB = receData.indexOf('B');
            int posS = receData.indexOf('S');
            String strPostB = receData.substring(posB + 1, posS);
            String strPostS = receData.substring(posS + 1);
            timeB = strPostB.toInt();
            timeS = strPostS.toInt();
            Serial.printf("B-%d S-%d\n", timeB, timeS);
            receData = "";
        }
    }
    if (millis() - oldTime >= timeB && flagShow == 2)
    {
        flagShow = 1;
        oldTime = millis();
    }
    if (millis() - oldTime >= timeS && flagShow == 1)
    {
        flagShow = 2;
        oldTime = millis();
    }
    for (int i = 0; i <= 7; i++)
    {
        dataRow = 1 << i;
        if (flagShow == 1)
        {
            dataCol = pic1[i];
        }
        if (flagShow == 2)
        {
            dataCol = pic2[i];
        }
        if (flagShow == -1)
        {
            dataCol = pic0[i];
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

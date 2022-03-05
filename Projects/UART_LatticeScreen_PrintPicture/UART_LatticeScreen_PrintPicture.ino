const int DATAPIN = 12;
const int CLOCKPIN = 13;
const int LATCHPIN = 14;

bool flagShow = 0;
String receData = "";
bool shapeFlag = 0;
unsigned long long oldTime = 0;
byte dataCol, dataRow;

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

void setup()
{
    digitalWrite(LATCHPIN, LOW);
    digitalWrite(CLOCKPIN, LOW);

    Serial.begin(9600);

    for (int i = 0; i <= 7; i++)
    {
        dataRow = 1 << i;
        dataCol = pic0[i];
        LCD_Display();
    }
}

void loop()
{
    String bTimeStr, sTimeStr;
    int bTime = 1000, sTime = 1000;
    if (Serial.available() > 0)
    {
        shapeFlag = 1;
        char dataBuff = Serial.read();
        if (dataBuff != '\r')
        {
            receData += dataBuff;
        }
        else
        {
            bTimeStr = receData.substring(receData.indexOf("B") + 1, receData.indexOf("S"));
            sTimeStr = receData.substring(receData.indexOf("S") + 1);
            bTime = bTimeStr.toInt();
            sTime = sTimeStr.toInt();
            Serial.print("B-");
            Serial.print(bTime);
            Serial.print(":S-");
            Serial.println(sTime);
        }
    }
    if (flagShow == 0 && millis() - oldTime >= bTime)
    {
        flagShow = !flagShow;
        oldTime = millis();
    }
    if (flagShow == 1 && millis() - oldTime >= sTime)
    {
        flagShow = !flagShow;
        oldTime = millis();
    }
    if (shapeFlag != 0)
    {
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
}

void LCD_Display()
{
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, dataCol);
    shiftOut(DATAPIN, CLOCKPIN, LSBFIRST, dataRow);
    digitalWrite(LATCHPIN, HIGH);
    digitalWrite(LATCHPIN, LOW);
}

const int DATAPIN = 12;
const int CLOCKPIN = 13;
const int LATCHPIN = 14;
const int POTPIN = 4;

byte dataRow, dataCol;

void setup() {
    pinMode(LATCHPIN, OUTPUT);
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(DATAPIN, OUTPUT);
    
    digitalWrite(CLOCKPIN, LOW);
    digitalWrite(LATCHPIN, LOW);

    analogSetWidth(10);
    
    Serial.begin(9600);
}

void loop() {
    for (int i = 0; i <= 7; i++)
    {
        dataRow = 1 << i;
        for (int j = 0; j <= 7; j++)
        {
            dataCol = ~(1 << j);
            delay(analogRead(POTPIN));
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

const int DATAPIN = 12;
const int CLOCKPIN = 13;
const int LATCHPIN = 14;

byte dataRow, dataCol;

void setup() {
    pinMode(LATCHPIN, OUTPUT);
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(DATAPIN, OUTPUT);
    digitalWrite(CLOCKPIN, LOW);
    digitalWrite(LATCHPIN, LOW);
    Serial.begin(9600);
}

void loop() {
    for (int i = 0; i <= 7; i++)
    {
        dataRow = 1 << i;
        dataCol = ~(1 << i);
        delay(100);
        LCD_Display();
    }
}

void LCD_Display()
{
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, dataCol);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, dataRow);
    digitalWrite(LATCHPIN, HIGH);
    digitalWrite(LATCHPIN, LOW);
}

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
    dataRow = 0b11111111;
    dataCol = 0b11100111;
    LCD_Display();
}

void LCD_Display()
{
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, dataCol);
    shiftOut(DATAPIN, CLOCKPIN, LSBFIRST, dataRow);
    digitalWrite(LATCHPIN, HIGH);
    digitalWrite(LATCHPIN, LOW);
}

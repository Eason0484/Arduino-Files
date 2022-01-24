const int DATAPIN = 12;
const int CLOCKPIN = 13;
const int LATCHPIN = 14;
const int POTPIN = 4;

byte dataRow, dataCol;

int pic[8] = { //Picture
    0b11101111,
    0b11000111,
    0b10000011,
    0b00000001,
    0b11101111,
    0b11101111,
    0b11101111,
    0b11111111,
};

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
        dataCol = pic[i];
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

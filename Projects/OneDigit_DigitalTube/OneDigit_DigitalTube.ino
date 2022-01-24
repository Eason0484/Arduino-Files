const int DATAPIN = 12; //ds
const int CLOCKPIN = 13; //CH_CP
const int LATCHPIN = 14; //ST_CP

const byte num[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xfe, 0xf6, 0x01};

//byte digits[11][8] = { //每个数字对应的开关数组
//  //{a, b, c, d, e, f, g, h}
//    {1, 1, 1, 1, 1, 1, 0, 0}, // 0  0xfc
//    {0, 1, 1, 0, 0, 0, 0, 0}, // 1  0x60
//    {1, 1, 0, 1, 1, 0, 1, 0}, // 2  0xda
//    {1, 1, 1, 1, 0, 0, 1, 0}, // 3  0xf2
//    {0, 1, 1, 0, 0, 1, 1, 0}, // 4  0x66
//    {1, 0, 1, 1, 0, 1, 1, 0}, // 5  0xb6
//    {1, 0, 1, 1, 1, 1, 1, 0}, // 6  0xbe
//    {1, 1, 1, 0, 0, 0, 0, 0}, // 7  0xe0
//    {1, 1, 1, 1, 1, 1, 1, 0}, // 8  0xfe
//    {1, 1, 1, 1, 0, 1, 1, 0}, // 9  0xf6
//    {0, 0, 0, 0, 0, 0, 0, 1}, // .  0x01
//};

void setup()
{
    pinMode(DATAPIN, OUTPUT);
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(LATCHPIN, OUTPUT);

    digitalWrite(CLOCKPIN, LOW);
    digitalWrite(LATCHPIN, LOW);
}

void loop()
{
    int i, j;
    for (j = 0; j <= 10; j++)
    {
        for (i = 0; i < 8; i++)
        {
            digitalWrite(DATAPIN, !bitRead(num[j], i));
            digitalWrite(CLOCKPIN, HIGH);
            digitalWrite(CLOCKPIN, LOW);
        }
        digitalWrite(LATCHPIN, HIGH);
        digitalWrite(LATCHPIN, LOW);
        delay(500);
    }
}

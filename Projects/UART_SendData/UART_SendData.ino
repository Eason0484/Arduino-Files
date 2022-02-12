void setup()
{
    char i = 48;
    byte NUM[] = {48, 49, 50, 51, 52, 53};
    Serial.begin(9600);
    Serial.println(123);
    Serial.println(123, BIN);
    Serial.println(123, HEX);
    Serial.println(12.3, 3);
    Serial.println(12, 3);
    Serial.write("ESP32");
    Serial.println();
    Serial.println("ESP32");
    Serial.write(123);
    Serial.println();
    Serial.println(i);
    Serial.write(NUM, 6);
}

void loop()
{
    
}

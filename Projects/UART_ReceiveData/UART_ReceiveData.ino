void setup()
{
    Serial.begin(9600);
}

void loop()
{
    if (Serial.available() > 0)
    {
        Serial.print(Serial.available());
        Serial.print('\t');

        int incomingByte = Serial.read();
        Serial.write(incomingByte);
        Serial.print('\t');
        Serial.println(incomingByte);
    }
}

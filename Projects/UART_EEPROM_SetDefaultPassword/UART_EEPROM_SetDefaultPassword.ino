#include "EEPROM.h";
String psw = "12345678";

void setup()
{
    EEPROM.begin(8);
    for (int i = 0; i < 8; i++)
    {
        EEPROM.write(i, psw[i]);
    }
    EEPROM.commit();
}

void loop()
{
}

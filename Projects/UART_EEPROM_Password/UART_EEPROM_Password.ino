#include "EEPROM.h";

bool state = 0;
bool modeFlag = 0;

String receData = "";
String psw = "";

void setup()
{
    Serial.begin(9600);
    EEPROM.begin(8);
    for (int i = 0; i < 8; i++)
    {
        psw += char(EEPROM.read(i));
    }
    Serial.println("Logged in as standard user.");
}

void loop()
{
    if (Serial.available() > 0)
    {
        char dataBuff = Serial.read();

        if (state == 0)
        {
            if (dataBuff == 'S' || dataBuff == 'P')
            {
                state = 1;
                receData = dataBuff;
            }
        }
        else
        {
            if (dataBuff == '\r')
            {
                state = 0;
                int strLen = receData.length();
                if (strLen != 9)
                {
                    Serial.println("Error message received.");
                }
                else
                {
                    String newpsw = receData.substring(1);

                    if (receData[0] == 'P' && newpsw == psw)
                    {
                        modeFlag = 1;
                        Serial.println("Logged in as root.");
                    }

                    if (receData[0] == 'S' && modeFlag == 1)
                    {
                        psw = newpsw;
                        for (int i = 0; i < 8; i++)
                        {
                            EEPROM.write(i, psw[i]);
                        }
                        EEPROM.commit();
                        Serial.println("Password reset.");
                        Serial.print("Enter new password: ");
                        Serial.println(psw);
                        modeFlag = 0;
                        Serial.println("Logged in as standard user.");
                    }
                }
            }
            else
            {
                receData += dataBuff;
            }
        }
    }
}

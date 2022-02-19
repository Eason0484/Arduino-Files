bool state = 0;
String receData = "";
int valM = 0;
int valH = 0;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    if (Serial.available() > 0)
    {
        char dataBuff = Serial.read();
        if (state == 0)
        {
            if (dataBuff == 'S')
            {
                state = 1;
                receData = "";
            }
        }
        else
        {
            if (dataBuff == '\r')
            {
                state = 0;
                int strLen = receData.length();
                if (strLen == 0)
                {
                    Serial.println("No data received!");
                }
                else
                {
                    String strH, strM;
                    int i = receData.indexOf(':');
                    strH = receData.substring(0, i);
                    strM = receData.substring(i + 1);
                    valH = strH.toInt();
                    valM = strM.toInt();
                    if ((valH > 23) || (valM > 59))
                    {
                        Serial.println("Error message received!");
                    }
                    else
                    {
                        Serial.printf("Set Hours: %d\tMinutes: %d\n", valH, valM);
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

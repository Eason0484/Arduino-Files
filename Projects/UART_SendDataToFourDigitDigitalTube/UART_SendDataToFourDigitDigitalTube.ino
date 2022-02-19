bool state = 0;
String receData = "";

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
            if (dataBuff == 'P')
            {
                state = 1;
                receData = "";
            }
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
                String strPostP, strPostS;
                int posP = receData.indexOf('P');
                int posS = receData.indexOf('S');
                strPostP = receData.substring(posP + 1, posS + 1);
                strPostS = receData.substring(posS + 1);
                int valPostP = strPostP.toInt();
                int valPostS = strPostS.toInt();
                Serial.printf("第一个数是: %d\n第二个数是: %d\n", valPostP, valPostS);
            }
            else
            {
                receData += dataBuff;
            }
        }
    }
}

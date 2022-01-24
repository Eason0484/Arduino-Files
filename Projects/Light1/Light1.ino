#define SWITCHPIN 4
#define LEDPIN 16
void setup() {
  // put your setup code here, to run once:
    pinMode(SWITCHPIN,INPUT);
    pinMode(LEDPIN,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    int val = digitalRead(SWITCHPIN);
    if(val == 0)
    {
        digitalWrite(LEDPIN,HIGH);
    }
    else
    {
        digitalWrite(LEDPIN,LOW);
    }
}

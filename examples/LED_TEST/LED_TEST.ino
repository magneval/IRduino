// led test of IRduino


void setup()
{
    for(int i=A0; i<=A5; i++)
    {
        pinMode(i, OUTPUT);
        digitalWrite(i, HIGH);
    }

    digitalWrite(A2, LOW);
    digitalWrite(A1, LOW);
    

}


void loop()
{

}
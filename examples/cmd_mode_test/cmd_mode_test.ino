// cmd mode test
// n cmd t_start t_stop ....
// Key, t_start, t_stop    unit in 10ms

#include <IRduino.h>

unsigned char cmd_buf[] = {3, KEY_LEFT_CTRL, 0, 10, KEY_RIGHT_ALT, 0, 10, KEY_DELETE, 5, 10};
unsigned char cmd_buf2[]  = {5, 'h', 0, 1, 'e', 2, 3, 'l', 4, 5, 'l', 6, 7, 'o', 8, 9};
unsigned char cmd_buf3[]  = {6, KEY_RIGHT_GUI, 0, 10, 'r', 5, 10, 'c', 11, 12, 'm', 13, 14, 'd', 15, 16, KEY_RETURN, 20, 21};


void setup()
{
    Serial.begin(115200);
    iRduino.begin();
}

void proc(unsigned char *cmd)
{
    if(NULL == cmd)return;
    
    int keyNum      = cmd[0];
    if(keyNum == 0)return;
    
    int maxTime     = 0;
    
    for(int i=0; i<keyNum; i++)
    {
        maxTime = (cmd[3+3*i] > maxTime) ? cmd[3+3*i] : maxTime;
    }
    
    int time_cnt    = 0;
    
    while(1)
    {
        // press or release some key
        for(int i=0; i<keyNum; i++)
        {
            if(time_cnt == cmd[3*i+2])
            {
                iRduino.press(cmd[3*i+1]);
            }
            else if(time_cnt == cmd[3*i+3])
            {
                iRduino.release(cmd[3*i+1]);
            }
        }
        
        time_cnt++;
        delay(10);
        if(time_cnt>maxTime)
        {
            iRduino.releaseAll();
            return;
        }

    }
}

void loop()
{
    if(iRduino.isGetIrDta())                              // get IR data
    {
        int irCode = iRduino.getIrDta();
        
        Serial.print("0x");
        Serial.println(irCode, HEX);
        
        if(0x1c == irCode)
        {
            Serial.println("get right data");
            iRduino.led(G1, 1);
            iRduino.led(G2, 1);
            delay(100);
            iRduino.led(G1, 0);
            iRduino.led(G2, 0);
            
            proc(cmd_buf3);
        }
    }

}
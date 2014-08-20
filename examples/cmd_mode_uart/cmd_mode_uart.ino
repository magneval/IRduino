// cmd mode test
// n cmd t_start t_stop ....
// Key, t_start, t_stop    unit in 10ms

#include <IRduino.h>
#include <EEPROM.h>
#include "cmd_mode_dfs.h"

#define DBG         1


unsigned char cmd_buf[] = {3, KEY_LEFT_CTRL, 0, 10, KEY_RIGHT_ALT, 0, 10, KEY_DELETE, 5, 10};
unsigned char cmd_buf2[]  = {5, 'h', 0, 1, 'e', 2, 3, 'l', 4, 5, 'l', 6, 7, 'o', 8, 9};
unsigned char cmd_buf3[]  = {6, KEY_RIGHT_GUI, 0, 10, 'r', 5, 10, 'c', 11, 12, 'm', 13, 14, 'd', 15, 16, KEY_RETURN, 20, 21};

unsigned char dtaLen = 0;
unsigned char dtaGet = 0;
unsigned char dtaBuf[50];



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

#if DBG        
        Serial.print("0x");
        Serial.println(irCode, HEX);
#endif
        if(0x1c == irCode)
        {
        
#if DBG
            Serial.println("get right data");
#endif
            iRduino.led(G1, 1);
            iRduino.led(G2, 1);
            delay(100);
            iRduino.led(G1, 0);
            iRduino.led(G2, 0);
            
            proc(cmd_buf3);
        }
    }
    
    if(dtaGet)
    {
        dtaGet = 0;
        uartDtaProc();
        dtaLen = 0;
    }
    
    serialEvent_1();
}

void uartDtaProc()
{
    if(dtaLen != (dtaBuf[1]+2))return;
    if(dtaBuf[0] > CMD_MAX_MAX)return;
    
    int __cmd = dtaBuf[0];
    switch(__cmd)
    {
        case CMD_WRITE_ITEM:
        write_item();
        break;
        
        case CMD_READ_ITEM:
        return_item(dtaBuf[2]);
        break;
    }
}

// write data to eeprom
void write_item()
{

    int item_num = dtaBuf[2];
    int keyNum = dtaBuf[3];
    
    
#if DBG
    Serial.println("write a item");
    Serial.print("item_num = ");
    Serial.println(item_num);
    Serial.print("keyNum = ");
    Serial.println(keyNum);
    Serial.println("EEPROM data: ");
#endif

    for(int i=0; i<(1+3*keyNum); i++)
    {
        EEPROM.write(50+50*item_num+i, dtaBuf[3+i]);
        
#if DBG
        Serial.print(50+50*item_num+i);
        Serial.print(": ");
        Serial.print("0x");
        Serial.println(dtaBuf[3+i], HEX);
#endif
    }
}

// return item
void return_item(int __item)
{
#if DBG
    Serial.println("return a item:");
#endif
    unsigned char dta[50];
    dta[0] = CMD_RETURN_ITEM;
    dta[2] = __item;
    
    int key_num = EEPROM.read(50+50*__item);
    dta[3] = key_num;
    for(int i=0; i<3*key_num; i++)
    {
        dta[4+i] = EEPROM.read(50+50*__item+i+1);
    }
    
    dta[1] = 3+3*key_num;
    dta[5+3*key_num] = 0xff;
    
    

    for(int i=0; i<(5+3*key_num); i++)
    {
#if DBG
        Serial.print("0x");
        Serial.print(dta[i], HEX);
        Serial.print("\t");
#endif
        //Serial.write(dta[i]);
    }
    
#if DBG
    Serial.println();
#endif

}

void serialEvent_1() 
{
    while (Serial.available()) 
    {
        dtaBuf[dtaLen++] = Serial.read();
        if(dtaBuf[dtaLen-1] == 0xff)          // stop while get an 0xff
        {
            dtaGet = 1;
        }
    }
}

#include <Arduino.h>
#include <IRDuino.h>
#include <IRDuinoRecv.h>

#define PINIR               6

#define __DBG               0

void IRDuino::begin()
{
    num_code= 0;

    Keyboard.begin();
    IR.Init(PINIR);
}


// press a key, then release it
void IRDuino::keyPressRelease(unsigned char keyNum)
{
    Keyboard.press(keyNum);
    delay(1);
    Keyboard.release(keyNum);
}

/*
 * enter a string
 */
void IRDuino::printf(char *str)
{
    if(NULL == str)return;

    while(*str)
    {
        keyPressRelease(str[0]);
        str++;
    }

}

/*
 * find if this ir code was stored, if not return -1
 */
int IRDuino::find_ir_code(int irCode)
{
    for(int i=0; i<num_code; i++)
    {
        if(irCode == ir_code[i])
        {
            return i;
        }
    }

    return -1;
}


/*
 * add an task
 */
bool IRDuino::addItem(int irCode, void (*pfun)())
{
    ir_code[num_code]    = irCode;
    task_fun[num_code++] = pfun;
}

/* process */
void IRDuino::process()
{
    if(!isGetIrDta())return;


    int irCode = getIrDta();

    Serial.println("+------------------------------------------------------+");
    if(irCode<=0)
    {
        Serial.println("get error code, try again");
    }
    else
    {
        Serial.print("get IR Code: 0x");
        Serial.println(irCode, HEX);
    }
    
    int task_loca = find_ir_code(irCode);
    
    if(task_loca >= 0)                  // find
    {
        Serial.print("task_loca = ");
        Serial.println(task_loca);
        (task_fun[task_loca])();
    }
    else
    {
        Serial.println("can't find this ir code");
    }
    
    Serial.println("+------------------------------------------------------+\r\n\r\n");
}



IRDuino iRduino;
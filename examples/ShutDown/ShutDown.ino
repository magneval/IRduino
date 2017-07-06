/*-------------------------------------------------------------------------- +
  Task_Mode_Empty.ino
  2014 Copyright (c) Longan Lab.  All right reserved.
 
  Author:Llama
  2014-7-25
  

  Function - 
  Shutdown your pc - only windows
  
  -------------------
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
-----------------------------------------------------------------------------*/
#include <IRDuino.h>

/*
 * define your IR code here
 */

#define IR_CODE_SHUT        0xBC
#define IR_CODE_CANCEL      0xF8

void setup()
{
    iRduino.begin();
    Serial.begin(115200);
    
/*
 * Add Item here
 */
    iRduino.addItem(IR_CODE_SHUT, task_shutdown);
    iRduino.addItem(IR_CODE_CANCEL, task_cancel_shutdown);
    
}


void loop()
{
    iRduino.process();
}


/*
 * Add your task here
 */
void task_shutdown()
{
    iRduino.winR();
    delay(100);
    iRduino.printf("shutdown -s -t 60");
    delay(10);
    iRduino.enter();
}

void task_cancel_shutdown()
{
    iRduino.winR();
    delay(100);
    iRduino.printf("shutdown /a");
    delay(100);
    iRduino.enter();
    iRduino.releaseAll();
}

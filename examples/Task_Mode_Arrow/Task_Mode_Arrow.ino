/*-------------------------------------------------------------------------- +
  Task_Mode_UDLR.ino
  2014 Copyright (c) Longan Lab.  All right reserved.
 
  Author:Llama
  2014-6-29
  
  Function - 
  It's Demo will access press up, down, left and right via 4 ir remote key.
  
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
     
// IR CODE DEFINE
#define IR_CODE_UP          0xee
#define IR_CODE_DOWN        0xae
#define IR_CODE_LEFT        0xce
#define IR_CODE_RIGHT       0x8e
#define IR_CODE_SPACE       0x72
     
void setup()
{
    iRduino.begin();
    Serial.begin(115200);
    
    // add task item
    iRduino.addItem(IR_CODE_UP, task_up);
    iRduino.addItem(IR_CODE_DOWN, task_down);
    iRduino.addItem(IR_CODE_LEFT, task_left);
    iRduino.addItem(IR_CODE_RIGHT, task_right);
    iRduino.addItem(IR_CODE_SPACE, task_space);
}


void loop()
{
    iRduino.process();
}

// add task

void task_up()
{
    iRduino.keyPressRelease(KEY_UP_ARROW);
}

void task_down()
{
    iRduino.keyPressRelease(KEY_DOWN_ARROW);
}

void task_left()
{
    iRduino.keyPressRelease(KEY_LEFT_ARROW);
}

void task_right()
{
    iRduino.keyPressRelease(KEY_RIGHT_ARROW);
}

void task_space()
{
    iRduino.keyPressRelease(KEY_SPACE);
}

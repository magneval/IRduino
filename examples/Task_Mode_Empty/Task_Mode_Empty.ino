/*-------------------------------------------------------------------------- +
  Task_Mode_Empty.ino
  2012 Copyright (c) Longan Lab.  All right reserved.
 
  Author:Loovee
  2014-6-29
  

  Function - 
  It's an empty task mode demo.
  You can add your task here
  Of curse you should get the IR code first - via the Get_IR_Code example
  
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

//#define IR_CODE_XXX   0x10

void setup()
{
    iRduino.begin();
    Serial.begin(115200);
    
/*
 * Add Item here
 */
    iRduino.addItem(IR_CODE_XXX, task_xxx);
    
}


void loop()
{
    iRduino.process();
}


/*
 * Add your task here
 */
void task_xxx()
{
    // add function
}

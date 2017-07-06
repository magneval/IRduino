/*-------------------------------------------------------------------------- +
  Write_String.ino
  2014 Copyright (c) Longan Lab.  All right reserved.
 
  Author:Llama
  2014-6-29
  
  Function - 
  Logout enter key in Window system.
  You sholed get a your ir remote key by the demo Get_IR_Code
  
  -------------------------------------------------------------
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

#define IRCODE_LOGOUT       0xEA
#define IRCODE_ENTERKEY     0x72

#define WINDOWS_KEY         "123456"

void setup()
{
    iRduino.begin();                            // initialize
}

void loop()
{
    if(iRduino.isGetIrDta())                    // get IR data
    {
        int irCode = iRduino.getIrDta();
        irCodeProcess(irCode);
    }
}


/*
 * process the ir command here
 */
void irCodeProcess(int irCode)
{
    if(irCode<=0)return;                        // error code
    
    switch(irCode)
    {
        case IRCODE_LOGOUT:                     // log out
        
        task_logout();
        
        break;
        
        case IRCODE_ENTERKEY:
        
        task_enterKey();

        default:;
    }
}


/*
 * Logout of windows
 */
void task_logout()
{
    iRduino.press(KEY_LEFT_CTRL);
    iRduino.press(KEY_LEFT_ALT);
    iRduino.press(KEY_DELETE);                  // Ctrl+Alt+Delete
    
    delay(500);                                 // delay 500ms
    
    
    iRduino.releaseAll();                       // release All

    iRduino.press(KEY_LEFT_ALT);           
    iRduino.press('k');                         // Alt+k

    delay(100);
    iRduino.releaseAll();                       // release All
}

/*
 * Enter Key
 */
void task_enterKey()
{
    iRduino.keyPressRelease(KEY_RETURN);        // press enter
    delay(500);
    iRduino.printf(WINDOWS_KEY);           // enter key
    iRduino.keyPressRelease(KEY_RETURN);        // release enter
}



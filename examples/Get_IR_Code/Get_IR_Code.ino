/*-------------------------------------------------------------------------- +
  GetIRCode.ino
  2014 Copyright (c) Longan Lab.  All right reserved.
 
  Author:Llama
  2014-6-29
  
  Function - 
  Insert your IRDuino, upload the code, then open Serial monitor,
  Choose baudrate 115200, then point your IR remote to IRduino,
  Press any key, you will get a Byte data. This is the code.
  
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
#include <IRduino.h>

#define INFO_STR "This is an demo of IRDuino - Get IR Code\r\nMore dtails refer to https://github.com/loovee/IRDuino\r\n\r\n"


void setup()
{
    Serial.begin(115200);
    while(!Serial);
    Serial.println(INFO_STR);
    
    iRduino.begin();
}

void loop()
{
    if(iRduino.isGetIrDta())                              // get IR data
    {
        int irCode = iRduino.getIrDta();
        
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
        Serial.println("+------------------------------------------------------+\r\n\r\n");
    }

}
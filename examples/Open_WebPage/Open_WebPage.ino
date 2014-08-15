/*-------------------------------------------------------------------------- +
  Open_WebPage.ino
  2014 Copyright (c) Longan Lab.  All right reserved.
 
  Author:Llama
  2014-7-6
  

  Function - 
  This demo will open a web page when you insert your IRDuino to a PC.
 
  https://github.com/LonganLab/IRduino
  
  This demo can only support Windows, not for linux and osx.
  
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

void openWebPage()
{
    iRduino.press(KEY_RIGHT_GUI);           // window
    iRduino.press('r');                     // win+R, you know that if you use a Windows system
    
    delay(200);
    iRduino.releaseAll();
    
    delay(100);
    
    iRduino.printf("iexplore.exe ");
    delay(100);
    iRduino.printf("longan.im");
    
    delay(100);
    iRduino.keyPressRelease(KEY_RETURN);

}

void setup()
{
    iRduino.begin();
    
    delay(1000);
    openWebPage();
}


void loop()
{
    //iRduino.process();
}

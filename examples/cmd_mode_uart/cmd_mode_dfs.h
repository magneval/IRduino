// cmd mode define 

#ifndef __CMD_MODE_DFS_H__
#define __CMD_MODE_DFS_H__

// CMD, LEN, DATA[...]
// PC -> IRduino
#define CMD_WRITE_ITEM      0X01            // write item to IRduino
#define CMD_READ_ITEM       0X02            // read item from IRduino
#define CMD_GET_ITEM_NUM    0X03            // get num of item from IRduino
#define CMD_READ_IR_CODE    0X04            // get IR code
#define CMD_RED_LED         0X05            // control red led of IRduino
#define CMD_GREEN_LED       0X06            // control green led
#define CMD_BLUE_LED        0X07            // control blue led
#define CMD_CLEAR_ALL_ITEM  0X08            // clear all the item
#define CMD_MAX_MAX         CMD_BLUE_LED    // max 


// IRduino -> PC
#define CMD_RETURN_ITEM     0X82            // return item to pc
#define CMD_RETURN_ITEM_NUM 0X83            // return item number
#define CMD_RETURN_IR_CODE  0X84            // return ir code

#endif
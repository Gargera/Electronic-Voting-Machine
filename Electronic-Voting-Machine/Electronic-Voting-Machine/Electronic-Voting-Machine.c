#include <util/delay.h>
#include "LCD.h"
#include "BUTTON.h"

#define  F_CPU   8000000UL
#define  MAX     100000

int main(void)
{
	
	LCD_init('C' , 4 , 'C' , 2 , 'C' , 1 , 'C' , 3 , 4);
	for(char i = 0 ; i < 4 ; i++) BUTTON_vInit('D' , i);
	
	LCD_vSend_string('C' , 4 , 'C' , 1 , 'C' , 3 , 4 , "A=    0,");
	LCD_movecursor(1 , 10 , 'C' , 4 , 'C' , 1 , 'C' , 3 , 4);
	LCD_vSend_string('C' , 4 , 'C' , 1 , 'C' , 3 , 4 , "B=    0");
	LCD_movecursor(2 , 1 , 'C' , 4 , 'C' , 1 , 'C' , 3 , 4);
	LCD_vSend_string('C' , 4 , 'C' , 1 , 'C' , 3 , 4 , "C=    0,");
	LCD_movecursor(2 , 10 , 'C' , 4 , 'C' , 1 , 'C' , 3 , 4);
	LCD_vSend_string('C' , 4 , 'C' , 1 , 'C' , 3 , 4 , "D=    0");
	
	LCD_vSend_cmd('C' , 4 , 'C' , 1 , 'C' , 3 , 4 , 0x04);
	
	int  data[] = {0, 0, 0, 0};
	char row[] = {1, 1, 2, 2} , col[] = {7, 16, 7, 16}; 
	
    while(1)
    {
	   signed char idx = -1;
	   for(char i = 0 ; i < 4 ; i++){
		   if(BUTTON_u8read('D' , i) != 0){
			  data[i] = (data[i] + 1)%MAX;
		      idx = i;
			  while(BUTTON_u8read('D' , i) != 0);
			  break;
		   }
	   }
	   
	   if(idx != -1){
	      char digits = 5;
		  int vData = data[idx];
		  LCD_movecursor(row[idx] , col[idx] , 'C' , 4 , 'C' , 1 , 'C' , 3 , 4);
		  
		  while(digits--){
			  if(vData == 0)
		          LCD_vSend_char('C' , 4 , 'C' , 1 , 'C' , 3 , 4 , ' ');
			  else
			      LCD_vSend_char('C' , 4 , 'C' , 1 , 'C' , 3 , 4 , vData%10 + '0');
			  vData /= 10;
		  }
	   }
    }
}

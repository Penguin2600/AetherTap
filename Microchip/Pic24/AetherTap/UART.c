/*
Engscope
UART
April 16, 2008
Author: JL
*/

#include "p24FJ64GA002.h"
#include "UART.h"

//Initiation function, parameter BRGVAL determines baud speed
void UART1Init(int BRGVAL)
{
   //Set up registers
   U1BRG = BRGVAL;	//set baud speed
   U1MODE	=	0x8000;	 //turn on module
   U1STA	=	0x8400;	 //set interrupts
   //reset RX interrupt flag
   IFS0bits.U1RXIF = 0;
}

//UART transmit function, parameter Ch is the character to send
void UART1PutChar(char Ch)
{
   //transmit ONLY if TX buffer is empty
   while(U1STAbits.UTXBF == 1);
   U1TXREG = Ch;
}

void UART1PutString(char str[], short len)
{
	int c;
	for(c = 0; c < (len-1); c++)
	{
		UART1PutChar(str[c]);
	}
}

//UART receive function, returns the value received.
char UART1GetChar()
{
   char Temp;
   //wait for buffer to fill up, wait for interrupt
   while(IFS0bits.U1RXIF == 0);
   Temp = U1RXREG;
   //reset interrupt
   IFS0bits.U1RXIF = 0;
   //return my received byte
   return Temp;
}

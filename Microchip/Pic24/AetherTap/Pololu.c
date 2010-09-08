#include "Pololu.h"

void PololuAbsPos(char srv, unsigned short val)
{
	// set lower byte value val[
	char d2 = (val & 0x7F);
	char d1 = (val >> 7);
	//create 6 byte serial packet [sync][id][command][servo][data1][data2]
	UART1PutChar(0x80);
	UART1PutChar(0x01);
	UART1PutChar(0x04);
	UART1PutChar(srv);
	UART1PutChar(d1);
	UART1PutChar(d2);
}

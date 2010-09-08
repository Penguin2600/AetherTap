//prototypes

//Initiation
extern void UART1Init(int BRGVAL);

//UART transmit function
extern void  UART1PutChar(char Ch);

extern void UART1PutString(char str[], short len);

//UART receive function
extern char UART1GetChar();

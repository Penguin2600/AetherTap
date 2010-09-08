
; PICBASIC PRO(TM) Compiler 2.47, (c) 1998, 2006 microEngineering Labs, Inc. All Rights Reserved.  
PM_USED			EQU	1

	INCLUDE	"16F88.INC"


; Define statements.
#define		CODE_SIZE		 4
#define		OSC		 20 

RAM_START       		EQU	00020h
RAM_END         		EQU	001EFh
RAM_BANKS       		EQU	00004h
BANK0_START     		EQU	00020h
BANK0_END       		EQU	0007Fh
BANK1_START     		EQU	000A0h
BANK1_END       		EQU	000EFh
BANK2_START     		EQU	00110h
BANK2_END       		EQU	0016Fh
BANK3_START     		EQU	00190h
BANK3_END       		EQU	001EFh
EEPROM_START    		EQU	02100h
EEPROM_END      		EQU	021FFh

R0              		EQU	RAM_START + 000h
R1              		EQU	RAM_START + 002h
R2              		EQU	RAM_START + 004h
R3              		EQU	RAM_START + 006h
R4              		EQU	RAM_START + 008h
R5              		EQU	RAM_START + 00Ah
R6              		EQU	RAM_START + 00Ch
R7              		EQU	RAM_START + 00Eh
R8              		EQU	RAM_START + 010h
FLAGS           		EQU	RAM_START + 012h
GOP             		EQU	RAM_START + 013h
RM1             		EQU	RAM_START + 014h
RM2             		EQU	RAM_START + 015h
RR1             		EQU	RAM_START + 016h
RR2             		EQU	RAM_START + 017h
_Counter         		EQU	RAM_START + 018h
_Command         		EQU	RAM_START + 01Ah
_Digi            		EQU	RAM_START + 01Bh
_DigiOne         		EQU	RAM_START + 01Ch
_DigiTen         		EQU	RAM_START + 01Dh
_Selector        		EQU	RAM_START + 01Eh
_test            		EQU	RAM_START + 01Fh
_PORTL           		EQU	 PORTB
_PORTH           		EQU	 PORTA
_TRISL           		EQU	 TRISB
_TRISH           		EQU	 TRISA
#define _Piezo           	_PORTB??3
#define _Tens            	_PORTA??0
#define _Ones            	_PORTA??1
#define _RX              	_PORTB??0
#define _TX              	_PORTB??1
#define _A               	_PORTB??4
#define _D               	_PORTB??5
#define _B               	_PORTB??6
#define _C               	_PORTB??7
#define _PORTB??3        	 PORTB, 003h
#define _PORTA??0        	 PORTA, 000h
#define _PORTA??1        	 PORTA, 001h
#define _PORTB??0        	 PORTB, 000h
#define _PORTB??1        	 PORTB, 001h
#define _PORTB??4        	 PORTB, 004h
#define _PORTB??5        	 PORTB, 005h
#define _PORTB??6        	 PORTB, 006h
#define _PORTB??7        	 PORTB, 007h

; Constants.
_T2400           		EQU	00000h
_T1200           		EQU	00001h
_T9600           		EQU	00002h
_T300            		EQU	00003h
_N2400           		EQU	00004h
_N1200           		EQU	00005h
_N9600           		EQU	00006h
_N300            		EQU	00007h
_OT2400          		EQU	00008h
_OT1200          		EQU	00009h
_OT9600          		EQU	0000Ah
_OT300           		EQU	0000Bh
_ON2400          		EQU	0000Ch
_ON1200          		EQU	0000Dh
_ON9600          		EQU	0000Eh
_ON300           		EQU	0000Fh
_MSBPRE          		EQU	00000h
_LSBPRE          		EQU	00001h
_MSBPOST         		EQU	00002h
_LSBPOST         		EQU	00003h
_LSBFIRST        		EQU	00000h
_MSBFIRST        		EQU	00001h
_CLS             		EQU	00000h
_HOME            		EQU	00001h
_BELL            		EQU	00007h
_BKSP            		EQU	00008h
_TAB             		EQU	00009h
_CR              		EQU	0000Dh
_UnitOn          		EQU	00012h
_UnitOff         		EQU	0001Ah
_UnitsOff        		EQU	0001Ch
_LightsOn        		EQU	00014h
_LightsOff       		EQU	00010h
_Dim             		EQU	0001Eh
_Bright          		EQU	00016h
	INCLUDE	"DEFCON.MAC"
	INCLUDE	"PBPPIC14.LIB"


	ASM?
 DEVICE PIC16F88,HS_OSC,MCLR_ON,LVP_OFF,WDT_OFF,PROTECT_OFF

	ENDASM?

	MOVE?CB	000h, CMCON
	MOVE?CB	000h, ADCON0
	MOVE?CB	000h, ANSEL
	MOVE?CB	001h, _Command
	MOVE?CB	001h, _Selector
	MOVE?CB	008h, _DigiTen
	MOVE?CB	008h, _DigiOne
	MOVE?CW	007D1h, _Counter
	PAUSE?C	032h
	SERPIN?T	_TX
	SERMODE?C	_T9600
	SEROUT?C	04Fh
	SEROUT?C	06Eh
	SEROUT?C	06Ch
	SEROUT?C	069h
	SEROUT?C	06Eh
	SEROUT?C	065h
	FREQOUTPIN?T	_Piezo
	FREQOUTTIME?C	064h
	FREQOUT?C	004E2h
	FREQOUTPIN?T	_Piezo
	FREQOUTTIME?C	064h
	FREQOUT?C	001F4h
	FREQOUTPIN?T	_Piezo
	FREQOUTTIME?C	064h
	FREQOUT?C	005DCh
	PAUSE?C	032h

	LABEL?L	_LOOP	
	ADD?WCW	_Counter, 001h, _Counter
	CMPLE?WCL	_Counter, 007D0h, L00001
	SERPIN?T	_TX
	SERMODE?C	_T9600
	SEROUT?C	050h
	SEROUT?C	069h
	SEROUT?C	06Eh
	SEROUT?C	067h
	SERPIN?T	_RX
	SERMODE?C	_T9600
	SERIND?B	_Command
	CMPNE?BCL	_Command, 000h, L00005
	MOVE?CW	000h, _Counter
	GOTO?L	L00004
	LABEL?L	L00005	
	CMPNE?BCL	_Command, 001h, L00006
	SERPIN?T	_TX
	SERMODE?C	_T9600
	SEROUT?C	050h
	SEROUT?C	069h
	SEROUT?C	06Eh
	SEROUT?C	067h
	MOVE?CW	007D1h, _Counter
	GOTO?L	L00004
	LABEL?L	L00006	
	CMPNE?BCL	_Command, 002h, L00007
	SERPIN?T	_RX
	SERMODE?C	_T9600
	SERIND?B	_DigiTen
	SERPIN?T	_RX
	SERMODE?C	_T9600
	SERIND?B	_DigiOne
	FREQOUTPIN?T	_Piezo
	FREQOUTTIME?C	064h
	FREQOUT?C	001F4h
	FREQOUTPIN?T	_Piezo
	FREQOUTTIME?C	064h
	FREQOUT?C	005DCh
	MOVE?CW	000h, _Counter
	GOTO?L	L00004
	LABEL?L	L00007	
	CMPNE?BCL	_Command, 003h, L00008
	SERPIN?T	_RX
	SERMODE?C	_T9600
	SERIND?B	_DigiTen
	SERPIN?T	_RX
	SERMODE?C	_T9600
	SERIND?B	_DigiOne
	FREQOUTPIN?T	_Piezo
	FREQOUTTIME?C	064h
	FREQOUT?C	004E2h
	MOVE?CW	000h, _Counter
	GOTO?L	L00004
	LABEL?L	L00008	
	MOVE?CW	000h, _Counter
	LABEL?L	L00004	
	LABEL?L	L00001	
	HIGH?T	_Tens
	MOVE?CB	001h, _Selector
	CALL?L	_dodigit
	PAUSE?C	005h
	LOW?T	_Tens
	HIGH?T	_Ones
	MOVE?CB	000h, _Selector
	CALL?L	_dodigit
	PAUSE?C	005h
	LOW?T	_Ones
	GOTO?L	_LOOP

	LABEL?L	_dodigit	
	CMPNE?BCL	_Selector, 000h, L00009
	MOVE?BB	_DigiOne, _Digi
	GOTO?L	L00010
	LABEL?L	L00009	
	MOVE?BB	_DigiTen, _Digi
	LABEL?L	L00010	
	CMPNE?BCL	_Digi, 000h, L00013
	CALL?L	_zero
	GOTO?L	L00012
	LABEL?L	L00013	
	CMPNE?BCL	_Digi, 001h, L00014
	CALL?L	_one
	GOTO?L	L00012
	LABEL?L	L00014	
	CMPNE?BCL	_Digi, 002h, L00015
	CALL?L	_two
	GOTO?L	L00012
	LABEL?L	L00015	
	CMPNE?BCL	_Digi, 003h, L00016
	CALL?L	_three
	GOTO?L	L00012
	LABEL?L	L00016	
	CMPNE?BCL	_Digi, 004h, L00017
	CALL?L	_four
	GOTO?L	L00012
	LABEL?L	L00017	
	CMPNE?BCL	_Digi, 005h, L00018
	CALL?L	_five
	GOTO?L	L00012
	LABEL?L	L00018	
	CMPNE?BCL	_Digi, 006h, L00019
	CALL?L	_six
	GOTO?L	L00012
	LABEL?L	L00019	
	CMPNE?BCL	_Digi, 007h, L00020
	CALL?L	_seven
	GOTO?L	L00012
	LABEL?L	L00020	
	CMPNE?BCL	_Digi, 008h, L00021
	CALL?L	_eight
	GOTO?L	L00012
	LABEL?L	L00021	
	CMPNE?BCL	_Digi, 009h, L00022
	CALL?L	_nine
	GOTO?L	L00012
	LABEL?L	L00022	
	RETURN?	
	LABEL?L	L00012	
	RETURN?	

	LABEL?L	_hi	
	HIGH?T	_A
	HIGH?T	_B
	HIGH?T	_C
	HIGH?T	_D
	RETURN?	

	LABEL?L	_zero	
	LOW?T	_A
	LOW?T	_B
	LOW?T	_C
	LOW?T	_D
	RETURN?	

	LABEL?L	_one	
	HIGH?T	_A
	LOW?T	_B
	LOW?T	_C
	LOW?T	_D
	RETURN?	

	LABEL?L	_two	
	LOW?T	_A
	HIGH?T	_B
	LOW?T	_C
	LOW?T	_D
	RETURN?	

	LABEL?L	_three	
	HIGH?T	_A
	HIGH?T	_B
	LOW?T	_C
	LOW?T	_D
	RETURN?	

	LABEL?L	_four	
	LOW?T	_A
	LOW?T	_B
	HIGH?T	_C
	LOW?T	_D
	RETURN?	

	LABEL?L	_five	
	HIGH?T	_A
	LOW?T	_B
	HIGH?T	_C
	LOW?T	_D
	RETURN?	

	LABEL?L	_six	
	LOW?T	_A
	HIGH?T	_B
	HIGH?T	_C
	LOW?T	_D
	RETURN?	

	LABEL?L	_seven	
	HIGH?T	_A
	HIGH?T	_B
	HIGH?T	_C
	LOW?T	_D
	RETURN?	

	LABEL?L	_eight	
	LOW?T	_A
	LOW?T	_B
	LOW?T	_C
	HIGH?T	_D
	RETURN?	

	LABEL?L	_nine	
	HIGH?T	_A
	LOW?T	_B
	LOW?T	_C
	HIGH?T	_D
	RETURN?	

	END

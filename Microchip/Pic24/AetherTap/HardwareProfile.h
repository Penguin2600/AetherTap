#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H

#include "GenericTypeDefs.h"
#include "Compiler.h"

//configuration fuse setting
#if defined(THIS_IS_STACK_APPLICATION)
_CONFIG2(FNOSC_FRCPLL & OSCIOFNC_ON &POSCMOD_NONE)		//HACKADAY: this is our custom oscillator configuration
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx3) //HACKADAY: define debugging pin pair 3, watchdog, jtag disabled.
#endif

//processor speed
#define GetSystemClock()		(32000000ul)
#define GetInstructionClock()	(GetSystemClock()/2)
#define GetPeripheralClock()	GetInstructionClock()

//HACKADAY: LED0 is server status LED,
// LED1 is SD card activity LED
// Hardware mappings
// LED I/O pins
//LED on RA2 and RB7
#define LED0_TRIS			TRISBbits.TRISB7		// ETH LED
#define LED0_IO				LATBbits.LATB7
#define LED1_TRIS			TRISAbits.TRISA3		// SD LED
#define LED1_IO				LATAbits.LATA3				

#define LED_GET()			(0)
#define LED_PUT(a)					


// AUX I/O pins
#define AUX0_TRIS			TRISBbits.TRISB0
#define AUX0_IO				LATBbits.LATB0
#define AUX1_TRIS			TRISAbits.TRISA1
#define AUX1_IO				LATAbits.LATA1
#define AUX2_TRIS			TRISAbits.TRISA0
#define AUX2_IO				LATAbits.LATA0
#define AUX3_TRIS			TRISBbits.TRISB15
#define AUX3_IO				LATBbits.LATB15

#define AUX_GET()			(0)
#define AUX_PUT(a)

//HACKADAY: make custom pin assignments for our hardware
// ENC28J60 I/O pins
//mapping:
//RB14(25)ETH-INT
//13/24 WOL
//12/23 MISO
//11/22 MOSI
//10/21 CLK
//9/18 CS
//8/17 RST
#define ENC_RST_TRIS		(TRISBbits.TRISB8)	
#define ENC_RST_IO			(PORTBbits.RB8)
#define ENC_CS_TRIS			(TRISBbits.TRISB9)
#define ENC_CS_IO			(PORTBbits.RB9)
// SPI SCK, SDI, SDO pins are automatically controlled by the 
// PIC24/dsPIC/PIC32 SPI module 
#define ENC_SPI_IF			(IFS0bits.SPI1IF)
#define ENC_SSPBUF			(SPI1BUF)
#define ENC_SPISTAT			(SPI1STAT)
#define ENC_SPISTATbits		(SPI1STATbits)
#define ENC_SPICON1			(SPI1CON1)
#define ENC_SPICON1bits		(SPI1CON1bits)
#define ENC_SPICON2			(SPI1CON2)

//HACKADAY:we use a SPI interface. hardware is setup below....
#define USE_SD_INTERFACE_WITH_SPI       // SD-SPI.c and .h

//HACKADAY:	define the SPI interface to use with the SD card
//if you use V1 prototype hardware be sure to check your pin configuration, 
//it will depend on the SD card holder you use.
#define SD_CS				LATAbits.LATA2
#define SD_CS_TRIS			TRISAbits.TRISA2
#define SD_CD				PORTAbits.RA2
#define SD_CD_TRIS			TRISAbits.TRISA2

//No write enable on V3 hardware
#define SD_WE				PORTBbits.RB4
#define SD_WE_TRIS			TRISBbits.TRISB4

//SPI module setup
#define SPICON1				SPI2CON1
#define SPISTAT				SPI2STAT
#define SPIBUF				SPI2BUF
#define SPISTAT_RBF			SPI2STATbits.SPIRBF
#define SPICON1bits			SPI2CON1bits
#define SPISTATbits			SPI2STATbits
#define SPIENABLE           SPI2STATbits.SPIEN

//TRIS for SCK/SDI/SDO lines
#define SPICLOCK			TRISBbits.TRISB2
#define SPIIN				TRISBbits.TRISB1
#define SPIOUT				TRISBbits.TRISB3

// Peripheral Pin Select Outputs
#define NULL_IO		0
#define C1OUT_IO	1
#define C2OUT_IO	2
#define U1TX_IO		3
#define U1RTS_IO	4
#define U2TX_IO		5
#define U2RTS_IO	6
#define SDO1_IO		7
#define SCK1OUT_IO	8
#define SS1OUT_IO	9
#define SDO2_IO		10
#define SCK2OUT_IO	11
#define SS2OUT_IO	12
#define OC1_IO		18
#define OC2_IO		19
#define OC3_IO		20
#define OC4_IO		21
#define OC5_IO		22

#endif

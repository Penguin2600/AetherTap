//Due to licensing issues, we can't redistribute the Microchip TCPIP stack or SD file system source. 
//You can get them from the Microchip website for free: 
//http://www.microchip.com/tcpip
//http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=2680&dDocName=en537999
//
//1.Download and install the TCPIP stack and the "File System for PIC18 PIC24 dsPIC PIC32" (SD file system). These files install to c:\Microchip Soultions\ by default.
//2.Place the Hack a Day project folder in the Microchip source install directory (c:\Microchip Soultions\ by default)
//3.That's it. You've got the latest source and we're compliant with the license.
//4.Depending on the install location you may need to tweak the include paths under Project->build options.
//
//We also can't redistribute the modified HTTP.c code from Microchip's TCPIP stack
//Instead, we included a patch (FATHTTP.patch) that shows the changes we made. 
//You can view the patch in a text editor, or apply it with a program like WinMerge (http://winmerge.org/) or TortoiseSVN.
//1. Find HTTP.c (\Microchip Solutions\Microchip\TCPIP Stack\HTTP.c) and copy it to the server project directory.
//2. Apply FATHTTP.patch to HTTP.c, call the new file FATHTTP.c.
//3. Done, the program should compile as intended.
// see README.TXT for complete instructions
//-------------------------------------


#define THIS_IS_STACK_APPLICATION //define as entry point

#include "FSIO.h" //HACKADAY:	include the FAT library.

#include "TCPIP Stack/TCPIP.h" //include TCPIP headers

#include "FATHTTP.h" //fat HTTP server adaptation
					//you MUST copy HTTP.c from the Microchip files and apply the FATHTTP.c patch
					//this is really a pain, but it's due to the Microchip redistribution prohibition...

//these variables must have these names because they're used externally in the stack
APP_CONFIG AppConfig; //holds TCPIP setup
static ROM BYTE SerializedMACAddress[6] = {MY_DEFAULT_MAC_BYTE1, MY_DEFAULT_MAC_BYTE2, MY_DEFAULT_MAC_BYTE3, MY_DEFAULT_MAC_BYTE4, MY_DEFAULT_MAC_BYTE5, MY_DEFAULT_MAC_BYTE6};

static void InitHardware(void);

int main(void){

	static TICK t = 0;
	
	InitHardware(); //setup hardware
	UART1Init(51); 	// // 51 for 19200 Baud. // 103 for 9600 @ 32Mhz

    TickInit();	//setup the tick timer

//HACKADAY:	init the FAT library for the FATHTTP server
	//while (!MDD_MediaDetect());
	while (!FSInit()); 	// Initialize the library

	//setup the TCPIP stack config variable
	AppConfig.Flags.bIsDHCPEnabled = TRUE;
	AppConfig.Flags.bInConfigMode = TRUE;
	memcpypgm2ram((void*)&AppConfig.MyMACAddr, (ROM void*)SerializedMACAddress, sizeof(AppConfig.MyMACAddr));
	AppConfig.MyIPAddr.Val = MY_DEFAULT_IP_ADDR_BYTE1 | MY_DEFAULT_IP_ADDR_BYTE2<<8ul | MY_DEFAULT_IP_ADDR_BYTE3<<16ul | MY_DEFAULT_IP_ADDR_BYTE4<<24ul;
	AppConfig.DefaultIPAddr.Val = AppConfig.MyIPAddr.Val;
	AppConfig.MyMask.Val = MY_DEFAULT_MASK_BYTE1 | MY_DEFAULT_MASK_BYTE2<<8ul | MY_DEFAULT_MASK_BYTE3<<16ul | MY_DEFAULT_MASK_BYTE4<<24ul;
	AppConfig.DefaultMask.Val = AppConfig.MyMask.Val;
	AppConfig.MyGateway.Val = MY_DEFAULT_GATE_BYTE1 | MY_DEFAULT_GATE_BYTE2<<8ul | MY_DEFAULT_GATE_BYTE3<<16ul | MY_DEFAULT_GATE_BYTE4<<24ul;
	AppConfig.PrimaryDNSServer.Val = MY_DEFAULT_PRIMARY_DNS_BYTE1 | MY_DEFAULT_PRIMARY_DNS_BYTE2<<8ul  | MY_DEFAULT_PRIMARY_DNS_BYTE3<<16ul  | MY_DEFAULT_PRIMARY_DNS_BYTE4<<24ul;
	AppConfig.SecondaryDNSServer.Val = MY_DEFAULT_SECONDARY_DNS_BYTE1 | MY_DEFAULT_SECONDARY_DNS_BYTE2<<8ul  | MY_DEFAULT_SECONDARY_DNS_BYTE3<<16ul  | MY_DEFAULT_SECONDARY_DNS_BYTE4<<24ul;

    StackInit(); 	//setup the stack
	HTTPInit();		//setup the fathttp server because it's not registered with the stack

    while(1){//never ending loop

        if(TickGet() - t >= TICK_SECOND/2ul){ //blink LED
            t = TickGet();
            LED0_IO ^= 1;
        }
		
		//service the stack, includes PING, DHCP client, etc
        StackTask();  
        StackApplications();
	
		HTTPServer();
		AndroidTask(); 
		

		#if defined(STACK_USE_ANNOUNCE) //announce IP address change if enabled
		if(dwLastIP != AppConfig.MyIPAddr.Val){
			dwLastIP = AppConfig.MyIPAddr.Val;
			AnnounceIP();
		}
		#endif

	

	}
}

//configures the PIC hardware
static void InitHardware(void){	
	AD1PCFG = 0xFFFF; //digital pins
	CLKDIVbits.RCDIV0=0; //clock divider to 0 **Improved over origional release**

/*********************************************************************
 *Setup LED and AUX IO
 *********************************************************************/

	//setup LEDs
	LED0_TRIS = 0;
	LED1_TRIS = 0;
	LED_PUT(0x00);

	//setup AUX Ports
	AUX0_TRIS = 0;
	AUX1_TRIS = 0;
	AUX2_TRIS = 0;
	AUX3_TRIS = 0;
	AUX_PUT(0x00);

/*********************************************************************
 *Setup PPS for UART and SPI
 *********************************************************************/


	// ENC28J60 I/O pins
	//RB14/PIN25 ETH-INT
	//13/24 WOL
	//12/23 MISO
	//11/22 MOSI
	//10/21 CLK
	//9/18 CS
	//8/17 RST

	// Inputs
	//MISO1 B12/23/RP12
	// Outputs
	//MOSI1 B11/22/RP11
	//CLK1 B10/21/RD10
	RPINR20bits.SDI1R = 12;			//SDI1 = RP12
	RPOR5bits.RP10R = SCK1OUT_IO; 	//RP10 = SCK1
	RPOR5bits.RP11R = SDO1_IO;		//RP11 = SDO1

	//SPI2 -> SD card
	//MISO2 B3/7
	//MOSI2 B1/5
	//CLK2 B2/6
	
	// Inputs
	//MISO2 B3/7/RP3
	// Outputs
	//MOSI2 B1/5/RP1
	//CLK2 B2/6/RP2
	RPINR22bits.SDI2R = 1;			//SDI2 = RP1	
	RPOR1bits.RP3R = SDO2_IO;		//RP1 = SDO2
	RPOR1bits.RP2R = SCK2OUT_IO; 	//RP2 = SCK2



	RPINR18bits.U1RXR	 =	0;	 //UART1 receive set to RB0
	RPOR7bits.RP15R	 =	3;	 //UART1 transmit set to RB15


	//lock PPS
	asm volatile (	"mov #OSCCON,w1 \n"
					"mov #0x46, w2 \n"
					"mov #0x57, w3 \n"
					"mov.b w2,[w1] \n"
					"mov.b w3,[w1] \n"
					"bset OSCCON, #6");
}

//stack overslow interrupt vectors
void _ISR __attribute__((__no_auto_psv__)) _AddressError(void)
{
    Nop();
	Nop();
}
void _ISR __attribute__((__no_auto_psv__)) _StackError(void)
{
    Nop();
	Nop();
}


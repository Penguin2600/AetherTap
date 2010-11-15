//this file enables different services in the Microchip stack
//see the example in ..\TCPIP Demo App in the Microchip Stack code for all possible options
#ifndef __TCPIPCONFIG_H
#define __TCPIPCONFIG_H

#include "GenericTypeDefs.h"
#include "Compiler.h"

//define the services to enable
//see the example in \Microchip Soutions\TCPIP Demo App\TCPIPConfig.h in the Microchip Stack code for all possible options
//#define STACK_USE_UART					// Application demo using UART for IP address display and stack configuration
//#define STACK_USE_UART2TCP_BRIDGE		// UART to TCP Bridge application example
//#define STACK_USE_IP_GLEANING
#define STACK_USE_ICMP_SERVER			// Ping query and response capability
#define STACK_USE_ICMP_CLIENT			// Ping transmission capability
//#define STACK_USE_HTTP_SERVER			// Old HTTP server
//#define STACK_USE_HTTP2_SERVER			// New HTTP server with POST, Cookies, Authentication, etc.
//#define STACK_USE_SSL_SERVER			// SSL server socket support (Requires SW300052)
//#define STACK_USE_SSL_CLIENT			// SSL client socket support (Requires SW300052)
#define STACK_USE_DHCP_CLIENT			// Dynamic Host Configuration Protocol client for obtaining IP address and other parameters
//#define STACK_USE_DHCP_SERVER			// Single host DHCP server
//#define STACK_USE_FTP_SERVER			// File Transfer Protocol (old)
//#define STACK_USE_SMTP_CLIENT			// Simple Mail Transfer Protocol for sending email
//#define STACK_USE_SNMP_SERVER			// Simple Network Management Protocol v2C Community Agent
//#define STACK_USE_TFTP_CLIENT			// Trivial File Transfer Protocol client
//#define STACK_USE_GENERIC_TCP_CLIENT_EXAMPLE	// HTTP Client example in GenericTCPClient.c
//#define STACK_USE_GENERIC_TCP_SERVER_EXAMPLE	// ToUpper server example in GenericTCPServer.c
#define STACK_USE_TELNET_SERVER			// Telnet server
#define STACK_USE_ANNOUNCE				// Microchip Embedded Ethernet Device Discoverer server/client
//#define STACK_USE_DNS					// Domain Name Service Client for resolving hostname strings to IP addresses
//#define STACK_USE_NBNS					// NetBIOS Name Service Server for repsonding to NBNS hostname broadcast queries
//#define STACK_USE_REBOOT_SERVER			// Module for resetting this PIC remotely.  Primarily useful for a Bootloader.
//#define STACK_USE_SNTP_CLIENT			// Simple Network Time Protocol for obtaining current date/time from Internet
//#define STACK_USE_UDP_PERFORMANCE_TEST	// Module for testing UDP TX performance characteristics.  NOTE: Enabling this will cause a huge amount of UDP broadcast packets to flood your network on the discard port.  Use care when enabling this on production networks, especially with VPNs (could tunnel broadcast traffic across a limited bandwidth connection).
//#define STACK_USE_TCP_PERFORMANCE_TEST	// Module for testing TCP TX performance characteristics
//#define STACK_USE_DYNAMICDNS_CLIENT		// Dynamic DNS client updater module
//#define STACK_USE_BERKELEY_API			// Berekely Sockets APIs are available


//MAC, IP settings, etc
#define MY_DEFAULT_HOST_NAME			"AetherTap"

#define MY_DEFAULT_MAC_BYTE1            (0x00)	
#define MY_DEFAULT_MAC_BYTE2            (0x04)	
#define MY_DEFAULT_MAC_BYTE3            (0xA3)	
#define MY_DEFAULT_MAC_BYTE4            (0x00)	
#define MY_DEFAULT_MAC_BYTE5            (0x00)	
#define MY_DEFAULT_MAC_BYTE6            (0x00)	

#define MY_DEFAULT_IP_ADDR_BYTE1        (192ul)
#define MY_DEFAULT_IP_ADDR_BYTE2        (168ul)
#define MY_DEFAULT_IP_ADDR_BYTE3        (0ul)
#define MY_DEFAULT_IP_ADDR_BYTE4        (122ul)

#define MY_DEFAULT_MASK_BYTE1           (255ul)
#define MY_DEFAULT_MASK_BYTE2           (255ul)
#define MY_DEFAULT_MASK_BYTE3           (255ul)
#define MY_DEFAULT_MASK_BYTE4           (0ul)

#define MY_DEFAULT_GATE_BYTE1           (192ul)
#define MY_DEFAULT_GATE_BYTE2           (168ul)
#define MY_DEFAULT_GATE_BYTE3           (0ul)
#define MY_DEFAULT_GATE_BYTE4           (1ul)

#define MY_DEFAULT_PRIMARY_DNS_BYTE1	(192ul)
#define MY_DEFAULT_PRIMARY_DNS_BYTE2	(168ul)
#define MY_DEFAULT_PRIMARY_DNS_BYTE3	(0ul)
#define MY_DEFAULT_PRIMARY_DNS_BYTE4	(1ul)

#define MY_DEFAULT_SECONDARY_DNS_BYTE1	(0ul)
#define MY_DEFAULT_SECONDARY_DNS_BYTE2	(0ul)
#define MY_DEFAULT_SECONDARY_DNS_BYTE3	(0ul)
#define MY_DEFAULT_SECONDARY_DNS_BYTE4	(0ul)

//use microchip stack in client more
#define STACK_CLIENT_MODE

//TCP Socket configuration
#define TCP_ETH_RAM_SIZE					(3900ul)
#define TCP_PIC_RAM_SIZE					(0ul)
#define TCP_SPI_RAM_SIZE					(0ul)
#define TCP_SPI_RAM_BASE_ADDRESS			(0x00)

//Define names of socket types
#define TCP_SOCKET_TYPES
	#define TCP_PURPOSE_GENERIC_TCP_CLIENT 0
	#define TCP_PURPOSE_GENERIC_TCP_SERVER 1
	#define TCP_PURPOSE_TELNET 2
	#define TCP_PURPOSE_FTP_COMMAND 3
	#define TCP_PURPOSE_FTP_DATA 4
	#define TCP_PURPOSE_TCP_PERFORMANCE_TX 5
	#define TCP_PURPOSE_TCP_PERFORMANCE_RX 6
	#define TCP_PURPOSE_UART_2_TCP_BRIDGE 7
	#define TCP_PURPOSE_HTTP_SERVER 8
	#define TCP_PURPOSE_DEFAULT 9
	#define TCP_PURPOSE_BERKELEY_SERVER 10
	#define TCP_PURPOSE_BERKELEY_CLIENT 11
#define END_OF_TCP_SOCKET_TYPES

#if defined(__TCP_C)
	#define TCP_CONFIGURATION
	ROM struct
	{
		BYTE vSocketPurpose;
		BYTE vMemoryMedium;
		WORD wTXBufferSize;
		WORD wRXBufferSize;
	} TCPSocketInitializer[] =
	{
		{TCP_PURPOSE_DEFAULT, TCP_ETH_RAM, 200, 200},
		{TCP_PURPOSE_HTTP_SERVER, TCP_ETH_RAM, 200, 200},
		{TCP_PURPOSE_TELNET, TCP_ETH_RAM, 200, 200},
		
	};
	#define END_OF_TCP_CONFIGURATION
#endif

// -- HTTP Server options -----------------------------------------------

	// Maximum numbers of simultaneous HTTP connections allowed.
	// Each connection consumes 2 bytes of RAM and a TCP socket
	#define MAX_HTTP_CONNECTIONS	(2u)

//we don't use this, but it's needed to prevent compiler errors
#define MAX_UDP_SOCKETS     (20u) 
#define UDP_USE_TX_CHECKSUM		


#endif


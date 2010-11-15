
#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"

#define ANDROID_PORT	2222

extern NODE_INFO remoteNode;

unsigned short	hval=3000;
unsigned short	vval=3000;

void AndroidTask(void)
{
	static enum {
		ANDROID_HOME = 0,
		ANDROID_LISTEN,
	} ANDROIDSM = ANDROID_HOME;

	static UDP_SOCKET	ASocket;
	BYTE 				i;
	
	switch(ANDROIDSM)
	{
		case ANDROID_HOME:
			// Open a UDP socket for inbound and outbound transmission
			// Since we expect to only receive broadcast packets and 
			// only send unicast packets directly to the node we last 
			// received from, the remote NodeInfo parameter can be anything
			ASocket = UDPOpen(ANDROID_PORT, NULL, ANDROID_PORT);

			if(ASocket == INVALID_UDP_SOCKET)
				return;
			else
				ANDROIDSM++;
			break;

		case ANDROID_LISTEN:
			// Do nothing if no data is waiting
			if(!UDPIsGetReady(ASocket))
				return;
			// See if this is a discovery query or reply
			UDPGet(&i);
			switch(i)
			{
				case 'r':
						UDPGetArray(&hval,2);
						UDPGetArray(&vval,2);
						PololuAbsPos(0, hval);
						PololuAbsPos(1, vval);
						UDPDiscard();
						break;
				case '0':
							LED1_IO ^= 1;
							break;
				case '1':
							LED1_IO ^= 1;
							break;
				case '2':
							LED1_IO ^= 1;
							break;
				case '3':
							AUX2_IO ^= 1;
							break;
				case '4':
							AUX3_IO ^= 1;
							break;
				default:
					break;
			}	
			UDPDiscard();	
			ANDROIDSM = ANDROID_LISTEN;
	}	

}

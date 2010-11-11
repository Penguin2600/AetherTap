
#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"

#define ANDROID_PORT	2222

extern NODE_INFO remoteNode;

unsigned short	hval=3000;
unsigned short	vval=3000;
BYTE	*Rhval;
BYTE	*Rvval;
static short staticdelta = 50;


void AndroidTask(void)
{
	static enum {
		ANDROID_HOME = 0,
		ANDROID_LISTEN,
		ANDROID_REQUEST_RECEIVED,
		ANDROID_DISABLED
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
					UDPGetArray(Rhval,2);
					UDPGetArray(Rvval,2);
					PololuAbsPos(0, &Rhval);
					PololuAbsPos(1, &Rvval);
				case 'w':
					vval+=staticdelta;
					PololuAbsPos(1, vval);
					break;
				case 's':
					vval-=staticdelta;
					PololuAbsPos(1, vval);
					break;
				case 'a':
					hval-=staticdelta;
					PololuAbsPos(0, hval);
					break;
				case 'd':
					hval+=staticdelta;
					PololuAbsPos(0, hval);
					break;
				case '1':
							LED1_IO ^= 1;
							break;
				case '2':
							AUX0_IO ^= 1;
							break;
				case '3':
							AUX1_IO ^= 1;
							break;
				case '4':
							AUX2_IO ^= 1;
							break;
				case '5':
							AUX3_IO ^= 1;
							break;
				default:
					break;
			}
			UDPDiscard();

			// We received a discovery request, reply when we can
			ANDROIDSM--;

			// Change the destination to the unicast address of the last received packet
        	memcpy((void*)&UDPSocketInfo[ASocket].remoteNode, (const void*)&remoteNode, sizeof(remoteNode));
			
			// No break needed.  If we get down here, we are now ready for the DISCOVERY_REQUEST_RECEIVED state

		case ANDROID_REQUEST_RECEIVED:
			if(!UDPIsPutReady(ASocket))
				return;

			// Begin sending our MAC address in human readable form.
			// The MAC address theoretically could be obtained from the 
			// packet header when the computer receives our UDP packet, 
			// however, in practice, the OS will abstract away the useful
			// information and it would be difficult to obtain.  It also 
			// would be lost if this broadcast packet were forwarded by a
			// router to a different portion of the network (note that 
			// broadcasts are normally not forwarded by routers).
			//UDPPutArray((BYTE*)AppConfig.NetBIOSName, sizeof(AppConfig.NetBIOSName)-1);
			UDPPut('\r');
			UDPPut(i);

			// Send the packet
			UDPFlush();

			// Listen for other discovery requests
			ANDROIDSM = ANDROID_LISTEN;
			break;

		case ANDROID_DISABLED:
			break;
	}	

}

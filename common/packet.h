#ifndef _PACKET_H_
#define _PACKET_H_

#include "koukaamtype.h"

/** SIMPLE BINARY PACKET PROCESSING UNIT     *
 * supports more then one message source     */

/* Example how to use it */
/*

#include "koukaamtype.h"
#include "packet.h"
#include "com.h"

void listenCom( void )
{
    packet_t pk;
        
    if( packetColector(0, &pk) == 1 )
    {
		// Do something interesting with data received
		// for example only
        switch( pk.type )
        {
			case 0:
				//send echo
				packetSender( 0, 0, pk.data, pk.dlen );
				break;

            case 1:
				//send RTC
                if(pk.dlen == sizeof(rtctime_t))
                    rtcSetTime((rtctime_t*)&pk.data);
                break;

            default:
                break;
        }
    }
}


int main( void )
{
	packetio_t pktio = { comGetc, comPutc };
	
	comInit();
	packetInit( &pktio, 1 );
	
	for(;;)
	{
	
		listenCom( void );	
	}
}
*/

/* Nejvetsi pripustna delka datove casti paketu */
#define PACKET_DLEN_MAX 32
/* Maximalni pocet zdroju dat (nastavit pokud mozno presne - mrha pameti */
#define PACKET_MAX_PORT_COUNT  2

/* Nastaveni parametru paketu */
#define PACKET_PREFIX_1  0x55
#define PACKET_PREFIX_2  0xAA
#define PACKET_SUM_MAGIC 0x23

#define rxPacketIndicator() 

typedef int (*getcfunc_t)(void);
typedef int (*putcfunc_t)(u8_t);

/* Transportni format */
typedef struct PACKET_S {
    u8_t type;
    u8_t dlen;
    u8_t data[ PACKET_DLEN_MAX ];
} packet_t;

typedef struct PACKETIO_S {
    getcfunc_t getFunc;
    putcfunc_t putFunc;
} packetio_t;

extern int packetInit( packetio_t *pktio, u8_t cnt);
extern int packetColector( u8_t port, packet_t *pack );
extern int packetSender( u8_t port, u8_t packetType, u8_t *payload, u8_t dlen );

#endif



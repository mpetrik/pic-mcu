#include <stdlib.h>
#include <string.h>
#include "koukaamtype.h"
#include "packet.h"

static u8_t        portCount = 0;
static packetio_t *pktio = NULL;
static u8_t        initialized = 0;

//--------------------------------------------------------------------------
int packetInit( packetio_t *pkt, u8_t cnt)
{
	
	initialized = 0;
	
	if( cnt > PACKET_MAX_PORT_COUNT )
		return -1;
		
	portCount = cnt;
        pktio = pkt;
	initialized = 1;
	return 0;
}

//--------------------------------------------------------------------------
int packetColector( u8_t port, packet_t *pack )
{
    int i;
    static packet_t pk[PACKET_MAX_PORT_COUNT]={0};
    static u8_t st[PACKET_MAX_PORT_COUNT] = {0};
    static u8_t idx[PACKET_MAX_PORT_COUNT] = {0};
    static u8_t sum[PACKET_MAX_PORT_COUNT];
    
	if( !initialized ) 
		return -1;
	
	if( port >= portCount )
		return -1;
	
    while(1)
    {
        if((i=pktio[port].getFunc()) == -1 )
            return 0;

        sum[port]+=i;
        
        switch( st[port] )
        {
                /* Startovaci sekvence paketu 0x55 0xAA */
            case 0:
                if( i==PACKET_PREFIX_1 ) st[port]++;
                break;

            case 1:
                if( i==PACKET_PREFIX_2 )
                {
                    sum[port]=PACKET_SUM_MAGIC;
                    st[port]++;
                }
                break;

                /* Typ paketu Byte */
            case 2:
                pk[port].type = i;
                st[port]++;
                break;

                /* Delka datove casti Byte */
            case 3:
                pk[port].dlen = i;
                idx[port]=0;
                st[port]++;
                if( pk[port].dlen > PACKET_DLEN_MAX )
                    st[port]=0;
                break;

                /* Data dlen x byte */
            case 4:
                pk[port].data[idx[port]++] = i;
                if( idx[port] == pk[port].dlen )
                    st[port]++;
                break;

                /* Check sum */
            case 5:
                sum[port]-=i;
                st[port] = 0;
                if( sum[port] == i )
                {
                    memcpy( pack, &pk[port], sizeof(packet_t));
                    rxPacketIndicator();
                    return 1;
                }
                break;
                
            default:
                st[port] = 0;
                break;
        }
    }
}

//--------------------------------------------------------------------------
int packetSender( u8_t port, u8_t packetType, u8_t *payload, u8_t dlen )
{
    packet_t pk;
    u8_t sum;
    u8_t i;
	
    if( !initialized )
        return -1;

    if( port >= portCount )
        return -1;

    if( dlen > PACKET_DLEN_MAX )
        return -1;

    pk.type = packetType;
    pk.dlen = dlen;
    memcpy( &pk.data, payload, dlen );


    pktio[port].putFunc( PACKET_PREFIX_1 );
    pktio[port].putFunc( PACKET_PREFIX_2 );
    for( sum=PACKET_SUM_MAGIC,i=0; i<dlen+2; i++ )
    {
        pktio[port].putFunc(((u8_t*)&pk)[i]);
        sum+=((u8_t*)&pk)[i];
    }
    pktio[port].putFunc(sum);

    return 0;
}


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------



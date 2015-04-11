/*****************************************************************************
 * File:        uart.c
 * Author:      Martin Petrik
 * Description: Driver for UART module
 ****************************************************************************/

/***********************CONSTANTS**************************************/

//uart sending protocol
typedef enum UART_FRAME_E {
    UART_HEAD,      //header const. value = 0xFE
    UART_LEN,       //data length
    UART_CONF,      //measure status
    UART_THIGH,     //High Byte Temperature
    UART_TLOW,      //Low Byte Temperature
    UART_CRC        //CRC
};
/***********************LOCAL VARIABLES**************************************/

volatile u8_t uartTxbuf[];
static   u8_t uartSts;

/*****************************************************************************
 * functions:   void uart_init
 * parameters:  none
 * return:      none
 ****************************************************************************/
static void uart_init( u8_t *buf )
{
    TXSTAbits.TXEN = 1;     //enable transmitter
    TXSTAbits.SYNC = 0;     //configure TX/CK I/O pin
    RCSTAbits.SPEN = 1;
    ANSEL = 0;
}

/*****************************************************************************
 * functions:   void interrupt uart_irq
 * parameters:  none
 * return:      none
 ****************************************************************************/
void interrupt uart_irq ( void )
{
    while( PIR1bits.TXIF );      //wait until flag is cleared

    //clear flag
    //load data2send into TX buffer
}

 /*****************************************************************************
 * functions:   u8_t uart_send
 * parameters:  u8_t *buf
 * return:      TRUE or FALSE
 ****************************************************************************/
u8_t uart_send ( s16_t *buf)
{
    switch(uartSts)
    {
        case UART_HEAD:
            TXREG = (*buf);
        return FALSE;
    }
}

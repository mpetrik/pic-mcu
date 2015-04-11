#ifndef _REGISTERFILE_H_
#define _REGISTERFILE_H_

#include "../common/types.h"
typedef struct REGISTERFILE_S{
	u16_t   value;
	u16_t   defVal;
	u16_t   writeMask;
	u16_t   eeMask;
} registerfile_t;

void     rfinit  ( registerfile_t *rf, u8_t count, u16_t ia ); 
u16_t    rfrd    ( u8_t idx );                    /* Get value from register IDX */
void     rfwr    ( u8_t idx, u16_t val );         /* Write VAL directly to the register IDX */
void     rfwrmask( u8_t idx, u16_t val );         /* Write VAL directly to the register IDX using Write mask - mainly for access from outside */
void     rfsbr   ( u8_t idx, u16_t bitmask );     /* Set bits defined by BITMASK in register IDX */
void     rfcbr   ( u8_t idx, u16_t bitmask );     /* Clear bits defined by BITMASK in register IDX */

/* Set(C is nonzero) or Clear(C is zero) bits defined by B in register A */
#define rfbr(a,b,c) \
     do { \
        if(c) \
           rfsbr(a,b); \
		else \
		   rfcbr(a,b); \
     } while(0)

#endif

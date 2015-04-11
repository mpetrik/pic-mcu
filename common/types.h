#ifndef _KOUKAAMTYPE_H_
#define _KOUKAAMTYPE_H_

#define clearFlag(a,b) a &= ~(b)
#define setFlag(a,b)   a |= (b)
#define isFlag(a,b)    ((a & (b))!=0)

typedef char s8_t;
typedef unsigned char u8_t;
typedef short s16_t;
typedef unsigned short u16_t;
typedef long s32_t;
typedef unsigned long u32_t;

#define INVALID_CHARACTER  -1

#define RETVAL_OK                0
#define RETVAL_ERROR            -1

#define STRINGERIZE(s) #s

#define DOWNLOAD_BUFFER_SIZE	250	// download buffer size RS232
#define UPLOAD_BUFFER_SIZE	250	// upload buffer size RS232

#ifndef NULL
#define NULL 0
#endif

typedef enum _BOOL { FALSE = 0, TRUE = 1 } BOOL;
typedef enum _TRIS {OUTPUT = 0, INPUT = 1} TRIS;
typedef enum _PORT {LOW = 0, HIGH = 1} PORT;

#endif


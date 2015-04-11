#ifndef _KOUKAAMLIBC_H_
#define _KOUKAAMLIBC_H_

int kstrlen( char *s );
int kstrcmp( char * s1, char * s2 );
int kstrcpy( char * s1, char * s2 );
int kstrncpy( char * s1, char * s2, u16_t num );
int kstrcat( char *s1, char * s2 );
int katoi( char * s );
unsigned int katoui( char * s );
// vytiskne do str  unsigned int cislo se zakladem b ( 2...16 )
int ksprintui( char * str, u16_t u, u8_t b );
// prevod retezce hexa znaku do long
unsigned int katox( char * s);
#endif

/*------------------------------------------------------------------------*/
/* Universal string handler for user console interface  (C)ChaN, 2011     */
/*------------------------------------------------------------------------*/

//#include "Specific_Config.h" - tmp


#ifndef __XPRINTF_H
#define __XPRINTF_H
// to prevent recursive inclusion

/**** tmp --***/
/****  Defines to use string functionalities over UART   ***********/
/**** allowing communication with a terminal like PuTTY  ***********/

#define __USE_XFUNC_OUT	1	/* 1: Use output functions */
#define	_CR_CRLF		1	/* 1: Convert \n ==> \r\n in the output char */

#define __USE_XFUNC_IN	1	/* 1: Use input function */
#define	_LINE_ECHO		0	/* 1: Echo back input chars in xgets function */
/**** tmp --***/



//#if __USE_XFUNC_OUT   tmp

/* Output Functions */

#define xdev_out(func) xfunc_out = (void(*)(unsigned char))(func)

extern void (*xfunc_out)(unsigned char);
void xputc (char c);
void xputs (const char* str);
void xfputs (void (*func)(unsigned char), const char* str);
void xprintf (const char* fmt, ...);
void xsprintf (char* buff, const char* fmt, ...);
void xfprintf (void (*func)(unsigned char), const char*	fmt, ...);
void put_dump (const void* buff, unsigned long addr, int len, int width);
#define DW_CHAR		sizeof(char)
#define DW_SHORT	sizeof(short)
#define DW_LONG		sizeof(long)

//#endif  /* __USE_XFUNC_OUT */   tmp



// #if __USE_XFUNC_IN tmp
  
/* Input Functions */

#define xdev_in(func) xfunc_in = (unsigned char(*)(void))(func)

extern unsigned char (*xfunc_in)(void);
int xgets (char* buff, int len);
int xfgets (unsigned char (*func)(void), char* buff, int len);
int xatoi (char** str, long* res);

//  #endif  /* __USE_XFUNC_IN */   tmp

#endif  /* __XPRINTF_H */

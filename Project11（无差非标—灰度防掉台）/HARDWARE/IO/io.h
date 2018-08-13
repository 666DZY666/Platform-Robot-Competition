#ifndef __IO_H
#define __IO_H
#include "sys.h"
//#define check PCout(1)
void IO_Init(void);
#define io1 PCin(10)
#define io2 PCin(3)
#define io3 PCin(0)
#define io4 PCin(13)
//#define io5 PDin(14)
//#define io6 PDin(15)
#endif
